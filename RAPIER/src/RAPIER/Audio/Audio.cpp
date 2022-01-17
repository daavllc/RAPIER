#include "rppch.h"
#include "Audio.h"

#include "RAPIER/Debug/Profiler.h"

#include <chrono>
using namespace std::chrono_literals;

namespace RAPIER::Audio
{
	std::thread* AudioThread::s_AudioThread = nullptr;
	std::atomic<bool> AudioThread::s_ThreadActive = false;
	std::atomic<std::thread::id> AudioThread::s_AudioThreadID = std::thread::id();

	std::queue<AudioFunctionCallback*> AudioThread::s_AudioThreadJobs;
	static std::queue<AudioFunctionCallback*> s_AudioThreadJobsLocal;
	std::mutex AudioThread::s_AudioThreadJobsLock;

	std::function<void(RAPIER::Timestep)> AudioThread::OnUpdateCallback = nullptr;
	RAPIER::Timer AudioThread::s_Timer;
	std::atomic<float> AudioThread::s_LastFrameTime = 0.0f;
	RAPIER::Timestep AudioThread::s_Timestep = 0.0f;

	bool AudioThread::Start()
	{
		if (s_ThreadActive)
			return false;

		s_ThreadActive = true;
		s_AudioThread = new std::thread([]
			{
				RP_PROFILE_THREAD("AudioThread");

				#if defined(RP_PLATFORM_WINDOWS)
					HRESULT r;
					r = SetThreadDescription(
						GetCurrentThread(),
						L"RAPIER Audio Thread"
					);
				#endif

				RP_CORE_INFO("Spinning up Audio Thread.");
				while (s_ThreadActive)
				{
					OnUpdate();
				}
				RP_CORE_INFO("Audio Thread stopped.");
			});

		s_AudioThreadID = s_AudioThread->get_id();
		s_AudioThread->detach();

		return true;
	}

	bool AudioThread::Stop()
	{
		if (!s_ThreadActive)
			return false;

		s_ThreadActive = false;
		return true;
	}

	bool AudioThread::IsRunning()
	{
		return s_ThreadActive;
	}

	bool AudioThread::IsAudioThread()
	{
		return std::this_thread::get_id() == s_AudioThreadID;
	}

	std::thread::id AudioThread::GetThreadID()
	{
		return s_AudioThreadID;
	}

	void AudioThread::AddTask(AudioFunctionCallback*&& funcCb)
	{
		RP_PROFILE_FUNC();

		std::scoped_lock lock(s_AudioThreadJobsLock);
		s_AudioThreadJobs.emplace(std::move(funcCb));
	}

	void AudioThread::OnUpdate()
	{
		RP_PROFILE_FUNC();

		s_Timer.Reset();

		//---------------------------
		//--- Handle AudioThread Jobs

		{
			RP_PROFILE_FUNC("AudioThread::OnUpdate - Execution");

			auto& jobs = s_AudioThreadJobsLocal;
			{
				std::scoped_lock lock(s_AudioThreadJobsLock);
				s_AudioThreadJobsLocal = s_AudioThreadJobs;
				s_AudioThreadJobs = std::queue<AudioFunctionCallback*>();
			}
			if (!jobs.empty())
			{
				// Should not run while jobs are not complete, instead re-add them to run on the next update loop
				for (int i = (int)jobs.size() - 1; i >= 0; i--)
				{
					auto job = jobs.front();
					//HZ_CONSOLE_LOG_INFO("AudioThread. Executing: {}", job->GetID());
					job->Execute();

					// TODO: check if job ran successfully, if not, notify and/or add back to the queue
					jobs.pop();
					delete job; // TODO: replace with smart pointer :[
				}
			}
		}

		RP_CORE_ASSERT(OnUpdateCallback != nullptr, "Update Function is not bound!");
		OnUpdateCallback(s_Timestep);


		std::this_thread::sleep_for(1ms);

		s_Timestep = s_Timer.Elapsed();
		s_LastFrameTime = s_Timestep.GetMilliseconds();
	}




}	//	END namespace RAPIER::Audio

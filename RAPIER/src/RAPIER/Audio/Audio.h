#pragma once

#include <thread>
#include <atomic>
#include <queue>

#include "RAPIER/Core/Timer.h"
#include "RAPIER/Core/Timestep.h"

namespace RAPIER
{
	class MiniAudioEngine;
}	//	END namespace RAPIER

namespace RAPIER::Audio
{
	static constexpr auto PCM_FRAME_CHUNK_SIZE = 1024;
	static constexpr auto STOPPING_FADE_MS = 28;
	static constexpr float SPEED_OF_SOUND = 343.3f;

	using AudioThreadCallbackFunction = std::function<void()>;

	class AudioFunctionCallback
	{
	public:
		AudioFunctionCallback(AudioThreadCallbackFunction f, const char* jobID = "NONE")
			: m_Func(std::move(f)), m_JobID(jobID)
		{}

		void Execute()
		{
			m_Func();
		}

		const char* GetID() { return m_JobID; }
	private:
		AudioThreadCallbackFunction const m_Func;
		const char* m_JobID;
	};

	class AudioThread
	{
	public:
		static bool Start();
		static bool Stop();
		static bool IsRunning();
		static bool IsAudioThread();
		static std::thread::id GetThreadID();

	private:
		friend class RAPIER::MiniAudioEngine;

		static void AddTask(AudioFunctionCallback*&& funcCb);
		static void OnUpdate();
		static float GetFrameTime() { return s_LastFrameTime.load(); }

		template<typename C, void (C::* Function)(Timestep)>
		static void BindUpdateFunction(C* instance)
		{
			OnUpdateCallback = [instance](Timestep ts) { (static_cast<C*>(instance)->*function)(ts); };
		}

		template<typename FuncT>
		static void BindUpdateFunction(FuncT&& func)
		{
			OnUpdateCallback = [func](Timesstep ts) { func(ts); };
		}
	private:
		static std::thread* s_AudioThread;
		static std::atomic<bool> s_ThreadActive;
		static std::atomic<std::thread::id> s_AudioThreadID;

		static std::queue<AudioFunctionCallback*> s_AudioThreadJobs;
		static std::mutex s_AudioThreadJobsLock;

		static std::function<void(Timestep)> OnUpdateCallback;
		static Timer s_Timer;
		static Timestep s_Timestep;
		static std::atomic<float> s_LastFrameTime;
	};

	static inline bool IsAudioThread()
	{
		return std::this_thread::get_id() == AudioThread::GetThreadID();
	}

	struct Transform
	{
		glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Orientation{ 0.0f, 0.0f, -1.0f };
		glm::vec3 Up{ 0.0f, 1.0f, 0.0f };

		bool operator==(const Transform& other) const
		{
			return Position == other.Position && Orientation == other.Orientation && Up == other.Up;
		}

		bool operator!=(const Transform& other) const
		{
			return !(*this == other);
		}
	};

	static inline float Lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}

	class SimpleBufferOperations
	{
	public:
		static inline void ApplyGainRamp(float* data, uint32_t numSamples, uint32_t numChannels, float gainStart, float gainEnd)
		{
			const float delta = (gainEnd - gainStart) / (float)numSamples;
			for (uint32_t i = 0; i < numSamples; ++i)
			{
				for (uint32_t ch = 0; ch < numChannels; ++ch)
					data[i * numChannels + ch] *= gainStart + delta * i;
			}
		}

		static inline void ApplyGainRampToSingleChannel(float* data, uint32_t numSamples, uint32_t numChannels, uint32_t channel, float gainStart, float gainEnd)
		{
			const float delta = (gainEnd - gainStart) / (float)numSamples;
			for (uint32_t i = 0; i < numSamples; ++i)
			{
				data[i * numChannels + channel] *= gainStart + delta * i;
			}
		}

		static inline void AddAndApplyGainRamp(float* dest, const float* source, uint32_t destChannel, uint32_t sourceChannel,
			uint32_t destNumChannels, uint32_t sourceNumChannels, uint32_t numSamples, float gainStart, float gainEnd)
		{
			if (gainEnd == gainStart)
			{
				for (uint32_t i = 0; i < numSamples; ++i)
					dest[i * destNumChannels + destChannel] += source[i * sourceNumChannels + sourceChannel] * gainStart;
			}
			else
			{
				const float delta = (gainEnd - gainStart) / (float)numSamples;
				for (uint32_t i = 0; i < numSamples; ++i)
				{
					dest[i * destNumChannels + destChannel] += source[i * sourceNumChannels + sourceChannel] * gainStart;
					gainStart += delta;
				}
			}
		}

		static inline void AddAndApplyGain(float* dest, const float* source, uint32_t destChannel, uint32_t sourceChannel,
			uint32_t destNumChannels, uint32_t sourceNumChannels, uint32_t numSamples, float gain)
		{
			for (uint32_t i = 0; i < numSamples; ++i)
				dest[i * destNumChannels + destChannel] += source[i * sourceNumChannels + sourceChannel] * gain;
		}

		static bool ContentMatches(const float* buffer1, const float* buffer2, uint32_t frameCount, uint32_t numChannels)
		{
			for (uint32_t frame = 0; frame < frameCount; ++frame)
			{
				for (uint32_t chan = 0; chan < numChannels; ++chan)
				{
					const auto pos = frame * numChannels + chan;
					if (buffer1[pos] != buffer2[pos])
						return false;
				}
			}
			return true;
		}
	};

}	//	END namespace RAPIER::Audio

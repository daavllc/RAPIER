#pragma once

#include "RAPIER/Editor/EditorConsolePanel.h"

#include <spdlog/sinks/base_sink.h>
#include <mutex>

namespace RAPIER
{
	class EditorConsoleSink : public spdlog::sinks::base_sink<std::mutex>
	{
	public:
		explicit EditorConsoleSink(uint32_t bufferCapacity)
			: m_MessageBufferCapacity(bufferCapacity), m_MessageBuffer(bufferCapacity) {}

		virtual ~EditorConsoleSink() = default;

		EditorConsoleSink(const EditorConsoleSink & other) = delete;
		EditorConsoleSink& operator=(const EditorConsoleSink & other) = delete;

	protected:
		void sink_it_(const spdlog::details::log_msg & msg) override
		{
			spdlog::memory_buf_t formatted;
			spdlog::sinks::base_sink<std::mutex>::formatter_->format(msg, formatted);
			m_MessageBuffer[m_MessageCount++] = ConsoleMessage(fmt::to_string(formatted), GetMessageCategory(msg.level));

			if (m_MessageCount == m_MessageBufferCapacity)
				flush_();
		}

		void flush_() override
		{
			for (const auto& message : m_MessageBuffer)
			{
				if (message.GetCategory() == ConsoleMessage::Category::None)
					continue;

				EditorConsolePanel::PushMessage(message);
			}

			m_MessageCount = 0;
		}

	private:
		static ConsoleMessage::Category GetMessageCategory(spdlog::level::level_enum level)
		{
			switch (level)
			{
			case spdlog::level::trace:
			case spdlog::level::debug:
			case spdlog::level::info:
				return ConsoleMessage::Category::Info;
			case spdlog::level::warn:
				return ConsoleMessage::Category::Warning;
			case spdlog::level::err:
			case spdlog::level::critical:
				return ConsoleMessage::Category::Error;
			}

			RP_CORE_ASSERT("Invalid Message Category!");
			return ConsoleMessage::Category::None;
		}

	private:
		uint32_t m_MessageBufferCapacity;
		std::vector<ConsoleMessage> m_MessageBuffer;
		uint32_t m_MessageCount = 0;
	};

}	//	END namespace RAPIER

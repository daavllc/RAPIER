#pragma once

#include "RAPIER/Core/Base.h"

#include <string>

namespace RAPIER
{
	class ConsoleMessage
	{
	public:
		enum class Category
		{
			None = -1,
			Info = BIT(0),
			Warning = BIT(1),
			Error = BIT(2)
		};

	public:
		ConsoleMessage()
			: m_MessageID(0), m_Message(""), m_Count(0), m_Category(Category::None) {}

		ConsoleMessage(const std::string& message, Category category)
			: m_MessageID(std::hash<std::string>()(message)), m_Message(message), m_Count(1), m_Category(category) {}

		uint32_t GetMessageID() const { return m_MessageID; }
		const std::string& GetMessage() const { return m_Message; }
		uint32_t GetCount() const { return m_Count; }
		Category GetCategory() const { return m_Category; }

	private:
		uint32_t m_MessageID;
		std::string m_Message;
		uint32_t m_Count;
		Category m_Category;

		friend class EditorConsolePanel;
	};
}	// END namespace RAPIER

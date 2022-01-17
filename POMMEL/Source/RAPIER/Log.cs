using System;
using System.Runtime.CompilerServices;

namespace RAPIER
{
	public static class Log
	{
		internal enum LogLevel
		{
			Trace = (1 << 0),
			Info = (1 << 1),
			Warn = (1 << 3),
			Error = (1 << 4),
			Critical = (1 << 5)
		}

		public static void Trace(string format, params object[] paremeters) => LogMessage_Native(LogLevel.Trace, string.Format(format, paremeters));
		public static void Info(string format, params object[] paremeters) => LogMessage_Native(LogLevel.Info, string.Format(format, paremeters));
		public static void Warn(string format, params object[] paremeters) => LogMessage_Native(LogLevel.Warn, string.Format(format, paremeters));
		public static void Error(string format, params object[] paremeters) => LogMessage_Native(LogLevel.Error, string.Format(format, paremeters));
		public static void Critical(string format, params object[] paremeters) => LogMessage_Native(LogLevel.Critical, string.Format(format, paremeters));

		public static void Trace(object value) => LogMessage_Native(LogLevel.Trace, value.ToString());
		public static void Info(object value) => LogMessage_Native(LogLevel.Info, value.ToString());
		public static void Warn(object value) => LogMessage_Native(LogLevel.Warn, value.ToString());
		public static void Error(object value) => LogMessage_Native(LogLevel.Error, value.ToString());
		public static void Critical(object value) => LogMessage_Native(LogLevel.Critical, value.ToString());

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal static extern void LogMessage_Native(LogLevel level, string formattedMessage);

	}
}

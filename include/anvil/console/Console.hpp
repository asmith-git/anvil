//Copyright 2023 Adam G. Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http ://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#ifndef ANVIL_CONSOLE_HPP
#define ANVIL_CONSOLE_HPP

#include <string>
#include <vector>
#include <deque>
#include "anvil/core/Keywords.hpp"
#include "anvil/core/OperatingSystem.hpp"

namespace anvil {
	enum ConsoleColour : uint8_t {
		CONSOLE_BLACK,
		CONSOLE_GREY_DARK,
		CONSOLE_GREY_LIGHT,
		CONSOLE_WHITE,
		CONSOLE_BLUE_LIGHT,
		CONSOLE_GREEN_LIGHT,
		CONSOLE_CYAN_LIGHT,
		CONSOLE_RED_LIGHT,
		CONSOLE_MAGENTA_LIGHT,
		CONSOLE_YELLOW_LIGHT,
		CONSOLE_BLUE_DARK,
		CONSOLE_GREEN_DARK,
		CONSOLE_CYAN_DARK,
		CONSOLE_RED_DARK,
		CONSOLE_MAGENTA_DARK,
		CONSOLE_YELLOW_DARK
	};

	struct ConsoleText {
		std::string text;
		ConsoleColour foreground_colour;
		ConsoleColour background_colour;

		ConsoleText();
		ConsoleText(const std::string& text);
		ConsoleText(const std::string& text, const ConsoleColour foreground);
		ConsoleText(const std::string& text, const ConsoleColour foreground, const ConsoleColour background);
	};

	class Console {
	public:
		struct State {
			std::vector<ConsoleText> text;
		};
	private:
		std::deque<State> _state_stack;
#if ANVIL_OS == ANVIL_WINDOWS
		void* _stdout_handle;
#endif

		void PrintNoState(ConsoleText text);
	public:
		Console();
		~Console();

		void Clear();
		void PushState();
		void PopState();
		State SaveState() const;
		void LoadState(const State& state);

		void Print(ConsoleText text);

		std::string InputString(const ConsoleText& prompt, const bool clear = true);
		std::string InputString();
		size_t InputChoice(const ConsoleText& prompt, const std::vector<ConsoleText>& options, const bool clear = true);
		size_t InputChoice(const ConsoleText& prompt, const std::vector<std::string>& options, const bool clear = true);
		size_t InputChoice(const ConsoleText& prompt, const std::vector<std::string>& options, const ConsoleColour foreground, const bool clear = true);
		size_t InputChoice(const ConsoleText& prompt, const std::vector<std::string>& options, const ConsoleColour foreground, const ConsoleColour background, const bool clear = true);
		size_t InputChoice(const std::string& prompt, const std::vector<std::string>& options, const bool clear = true);
		size_t InputChoice(const std::string& prompt, const std::vector<std::string>& options, const ConsoleColour foreground, const bool clear = true);
		size_t InputChoice(const std::string& prompt, const std::vector<std::string>& options, const ConsoleColour foreground, const ConsoleColour background, const bool clear = true);

		ANVIL_STRONG_INLINE void Print(const std::string& text) { Print(ConsoleText(text)); }
		ANVIL_STRONG_INLINE void Print(const std::string& text, const ConsoleColour foreground) { Print(ConsoleText(text, foreground)); }
		ANVIL_STRONG_INLINE void Print(const std::string& text, const ConsoleColour foreground, const ConsoleColour background) { Print(ConsoleText(text, foreground, background)); }
		ANVIL_STRONG_INLINE std::string InputString(const std::string& text) { return InputString(ConsoleText(text)); }
		ANVIL_STRONG_INLINE std::string InputString(const std::string& text, const ConsoleColour foreground) { return InputString(ConsoleText(text, foreground)); }
		ANVIL_STRONG_INLINE std::string InputString(const std::string& text, const ConsoleColour foreground, const ConsoleColour background) { return InputString(ConsoleText(text, foreground, background)); }
		ANVIL_STRONG_INLINE void EndLine() { Print("\n"); }
	};
}

#endif
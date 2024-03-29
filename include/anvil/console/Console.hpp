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
#include <mutex>
#include "anvil/core/Keywords.hpp"
#include "anvil/core/OperatingSystem.hpp"

namespace anvil {

	namespace detail {
		enum {
			CONSOLE_BLUE = 1,
			CONSOLE_GREEN = 2,
			CONSOLE_RED = 4,
			CONSOLE_LIGHT = 8
		};
	}

	enum ConsoleColour : uint8_t {
		CONSOLE_BLACK = 0,
		CONSOLE_RED_DARK = detail::CONSOLE_RED,
		CONSOLE_RED_LIGHT = CONSOLE_RED_DARK | detail::CONSOLE_LIGHT,
		CONSOLE_GREEN_DARK = detail::CONSOLE_GREEN,
		CONSOLE_GREEN_LIGHT = CONSOLE_GREEN_DARK | detail::CONSOLE_LIGHT,
		CONSOLE_BLUE_DARK = detail::CONSOLE_BLUE,
		CONSOLE_BLUE_LIGHT = CONSOLE_BLUE_DARK | detail::CONSOLE_LIGHT,
		CONSOLE_YELLOW_DARK = CONSOLE_RED_DARK | CONSOLE_GREEN_DARK,
		CONSOLE_YELLOW_LIGHT = CONSOLE_YELLOW_DARK | detail::CONSOLE_LIGHT,
		CONSOLE_MAGENTA_DARK = CONSOLE_RED_DARK | CONSOLE_BLUE_DARK,
		CONSOLE_MAGENTA_LIGHT = CONSOLE_MAGENTA_DARK | detail::CONSOLE_LIGHT,
		CONSOLE_CYAN_DARK = CONSOLE_GREEN_DARK | CONSOLE_BLUE_DARK,
		CONSOLE_CYAN_LIGHT = CONSOLE_CYAN_DARK | detail::CONSOLE_LIGHT,
		CONSOLE_GREY_DARK = detail::CONSOLE_LIGHT,
		CONSOLE_GREY_LIGHT = CONSOLE_RED_DARK | CONSOLE_GREEN_DARK | CONSOLE_BLUE_DARK,
		CONSOLE_WHITE = CONSOLE_GREY_DARK | CONSOLE_GREY_LIGHT
	};

	class Console;

	class ANVIL_DLL_EXPORT ConsoleText {
	private:
		std::string _text;
		#pragma warning( disable : 4201) // Unnamed struct
		struct {
			uint32_t _char : 8u;
			uint32_t _foreground_colour : 4u;
			uint32_t _background_colour : 4u;
			uint32_t _is_char : 1u;
			uint32_t _unused : 15u;
		};
	public:
		friend Console;

		ConsoleText();
		ConsoleText(const char text, const ConsoleColour foreground = CONSOLE_WHITE, const ConsoleColour background = CONSOLE_BLACK);
		ConsoleText(const std::string& text, const ConsoleColour foreground = CONSOLE_WHITE, const ConsoleColour background = CONSOLE_BLACK);
	};

	class ANVIL_DLL_EXPORT Console {
	public:
		struct State {
			std::vector<ConsoleText> text;
		};
#if ANVIL_OS == ANVIL_WINDOWS
		enum { CURSOR_POSITION_SUPPORTED = 1 };
#else
		enum { CURSOR_POSITION_SUPPORTED = 0 };
#endif
	private:
		std::deque<State> _state_stack;
#if ANVIL_OS == ANVIL_WINDOWS
		void* _stdout_handle;
		uint16_t _current_attribute;
#endif
		uint16_t _state_lock;
	public:
		Console();
		~Console();

		/*!
			\brief Clear the console screen
		*/
		void Clear();

		/*!
			\brief Clear the current line
		*/
		void ClearLine();

		/*!
			\brief Remember what is currently written on the console
			\see PopState
		*/
		const State& PushState();

		/*!
			\brief Restore the console to the state it was in last time PushState() was called
			\see PushState
		*/
		void PopState();

		/*!
			\brief Save what is currently written to the console
			\return The contents of the console
			\see LoadState
		*/
		State SaveState() const;

		/*!
			\brief Restore the console to a previous state
			\param state The contents to write to the console
			\see SaveState
		*/
		void LoadState(const State& state);

		/*!
			\brief Returns true if the cursor position is at the start of a line
		*/
		bool IsAtStartOfLine() const;

		/*!
			\brief Return the width and height of the console in characters
		*/
		std::pair<size_t, size_t> GetSize() const;

		/*!
			\brief Return the position of the cursor
		*/
		std::pair<size_t, size_t> GetCursorLocation() const;

		/*!
			\brief Set the position of the cursor
		*/
		void SetCursorLocation(size_t x, size_t y);
		ANVIL_STRONG_INLINE void SetCursorLocation(std::pair<size_t, size_t> pos) { SetCursorLocation(pos.first, pos.second); }

		/*!
			\brief State changes will not be recorded until UnlockState is called
			\see UnlockState
		*/
		ANVIL_STRONG_INLINE void LockState() { ++_state_lock; }

		/*!
			\brief Allows new information to be written to the current state
			\see LockState
		*/
		ANVIL_STRONG_INLINE void UnlockState() { if (_state_lock > 0u) --_state_lock; }

		/*!
			\brief Check if the state is locked.
			\see LockState
			\see UnlockState
		*/
		ANVIL_STRONG_INLINE bool IsStateLocked() const { return _state_lock > 0; }

		/*!
			\brief Display text on the console
		*/
		void Print(const ConsoleText& text);

		/*!
			\brief Display a progress bar on the console
			\detail Will block until \a percentage is >= 100
			\param percentage The current progress as a percentage
			\param colour The colour of the progress bar
		*/
		void ProgressBar(float& percentage, ConsoleColour colour = CONSOLE_GREEN_LIGHT);

		/*!
			\brief Get an input from the user
			\return User input
		*/
		std::string InputString();

		/*!
			\brief Prompt the user to select from multiple choices
			\param prompt A description of the choice
			\param options A list of options to choose from
			\return The index in \a options that was selected
		*/
		size_t InputChoice(const ConsoleText& prompt, const std::vector<ConsoleText>& options);
		size_t InputChoice(const ConsoleText& prompt, const std::vector<std::string>& options);
		size_t InputChoice(const std::string& prompt, const std::vector<std::string>& options, const ConsoleColour foreground = CONSOLE_WHITE, const ConsoleColour background = CONSOLE_BLACK);
		ANVIL_STRONG_INLINE size_t InputChoice(const std::vector<ConsoleText>& options) { return InputChoice(ConsoleText(), options); }
		ANVIL_STRONG_INLINE size_t InputChoice(const std::vector<std::string>& options) { return InputChoice(ConsoleText(), options); }

		ANVIL_STRONG_INLINE void Print(const std::string& text, const ConsoleColour foreground = CONSOLE_WHITE, const ConsoleColour background = CONSOLE_BLACK) { Print(ConsoleText(text, foreground, background)); }
		ANVIL_STRONG_INLINE size_t GetWidth() const { return GetSize().first; }
		ANVIL_STRONG_INLINE size_t GetHeight() const { return GetSize().first; }

		ANVIL_STRONG_INLINE void Print(char c, const ConsoleColour foreground = CONSOLE_WHITE, const ConsoleColour background = CONSOLE_BLACK) { Print(ConsoleText(c, foreground, background)); }

		inline void Print(const std::string& text0, const ConsoleColour colour0, const std::string& text1, const ConsoleColour colour1) { 
			Print(text0, colour0);
			Print(text1, colour1);
		}

		inline void Print(const std::string& text0, const ConsoleColour colour0, const std::string& text1, const ConsoleColour colour1, const std::string& text2, const ConsoleColour colour2) {
			Print(text0, colour0);
			Print(text1, colour1);
			Print(text2, colour2);
		}

		inline void Print(const std::string& text0, const ConsoleColour colour0, const std::string& text1, const ConsoleColour colour1, const std::string& text2, const ConsoleColour colour2, const std::string& text3, const ConsoleColour colour3) {
			Print(text0, colour0);
			Print(text1, colour1);
			Print(text2, colour2);
			Print(text3, colour3);
		}

		inline void Print(const std::string& text0, const ConsoleColour colour0, const std::string& text1, const ConsoleColour colour1, const std::string& text2, const ConsoleColour colour2, const std::string& text3, const ConsoleColour colour3, const std::string& text4, const ConsoleColour colour4) {
			Print(text0, colour0);
			Print(text1, colour1);
			Print(text2, colour2);
			Print(text3, colour3);
			Print(text4, colour4);
		}

		ANVIL_STRONG_INLINE void EndLine() { Print('\n'); }
	};
}

#endif
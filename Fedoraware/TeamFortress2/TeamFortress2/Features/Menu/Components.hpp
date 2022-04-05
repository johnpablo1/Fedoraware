#pragma once
#include "ImGui/imgui_internal.h"

namespace ImGui
{
	/* Color_t to ImVec4 */
	inline ImVec4 mColor(Color_t color) {
		return ImVec4(Color::TOFLOAT(color.r), Color::TOFLOAT(color.g), Color::TOFLOAT(color.b), Color::TOFLOAT(color.a));
	}

	/* ImVec4 to Color_t */
	inline Color_t vColor(ImVec4 color) {
		return {
			static_cast<byte>(color.x * 256.0f > 255 ? 255 : color.x * 256.0f),
			static_cast<byte>(color.y * 256.0f > 255 ? 255 : color.y * 256.0f),
			static_cast<byte>(color.z * 256.0f > 255 ? 255 : color.z * 256.0f),
			static_cast<byte>(color.w * 256.0f > 255 ? 255 : color.w * 256.0f)
		};
	}

	__inline void HelpMarker(const char* desc)
	{
		// TODO: This
	}

	__inline bool SidebarButton(const char* label, bool active = false)
	{
		if (active) { PushStyleColor(ImGuiCol_Button, ImColor(38, 38, 38).Value); }
		const bool pressed = Button(label, { GetWindowSize().x - 2 * GetStyle().WindowPadding.x, 44.f });
		if (active) { PopStyleColor(); }
		return pressed;
	}

	__inline bool TabButton(const char* label, bool active = false)
	{
		TableNextColumn();
		if (active) { PushStyleColor(ImGuiCol_Button, GetColorU32(ImGuiCol_ButtonActive)); }
		const bool pressed = Button(label, { GetColumnWidth(), g_Menu.TabHeight });
		if (active) { PopStyleColor(); }
		return pressed;
	}

    /* Container for feature groups */
	__inline bool BeginContainer(const char* str_id)
	{
		PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.f, 8.f));
		PushStyleColor(ImGuiCol_Text, g_Menu.TextDark.Value);
		const bool open = CollapsingHeader(str_id, ImGuiTreeNodeFlags_DefaultOpen);
		PopStyleColor();
		PopStyleVar();
		return open;
	}

    __inline bool InputKeybind(const char* label, CVar<int>& output, bool bAllowNone = true)
	{
		auto VK2STR = [&](const short key) -> const char* {
			switch (key) {
			case VK_LBUTTON: return "LMB";
			case VK_RBUTTON: return "RMB";
			case VK_MBUTTON: return "MMB";
			case VK_XBUTTON1: return "Mouse4";
			case VK_XBUTTON2: return "Mouse5";
			case VK_SPACE: return "Space";
			case 0x0: return "None";
			case VK_A: return "A";
			case VK_B: return "B";
			case VK_C: return "C";
			case VK_D: return "D";
			case VK_E: return "E";
			case VK_F: return "F";
			case VK_G: return "G";
			case VK_H: return "H";
			case VK_I: return "I";
			case VK_J: return "J";
			case VK_K: return "K";
			case VK_L: return "L";
			case VK_M: return "M";
			case VK_N: return "N";
			case VK_O: return "O";
			case VK_P: return "P";
			case VK_Q: return "Q";
			case VK_R: return "R";
			case VK_S: return "S";
			case VK_T: return "T";
			case VK_U: return "U";
			case VK_V: return "V";
			case VK_W: return "W";
			case VK_X: return "X";
			case VK_Y: return "Y";
			case VK_Z: return "Z";
			case VK_0: return "0";
			case VK_1: return "1";
			case VK_2: return "2";
			case VK_3: return "3";
			case VK_4: return "4";
			case VK_5: return "5";
			case VK_6: return "6";
			case VK_7: return "7";
			case VK_8: return "8";
			case VK_9: return "9";
			case VK_ESCAPE: return "Escape";
			case VK_SHIFT: return "Shift";
			case VK_LSHIFT: return "Shift";
			case VK_RSHIFT: return "Shift";
			case VK_CONTROL: return "Control";
			case VK_MENU: return "LAlt";
			case VK_PRIOR: return "Page Up";
			case VK_NEXT: return "Page Down";
			default: break;
			}

			WCHAR output[16] = { L"\0" };
			if (const int result = GetKeyNameTextW(MapVirtualKeyW(key, MAPVK_VK_TO_VSC) << 16, output, 16)) {
				char outputt[128];
				sprintf(outputt, "%ws", output);
				return outputt;
			}

			return "VK2STR_FAILED";
		};

		const auto id = GetID(label);
		PushID(label);

		if (GetActiveID() == id) {
			Button("...", ImVec2(100, 20));

			static float time = g_Interfaces.Engine->Time();
			const float elapsed = g_Interfaces.Engine->Time() - time;
			static CVar<int>* curr = nullptr, * prevv = curr;
			if (curr != prevv) {
				time = g_Interfaces.Engine->Time();
				prevv = curr;
			}

			if (curr == nullptr && elapsed > 0.1f) {
				for (short n = 0; n < 256; n++) {
					if ((n > 0x0 && n < 0x7) ||
						(n > L'A' - 1 && n < L'Z' + 1) ||
						(n > L'0' - 1 && n < L'9' + 1) ||
						n == VK_LSHIFT ||
						n == VK_RSHIFT ||
						n == VK_SHIFT ||
						n == VK_ESCAPE ||
						n == VK_HOME ||
						n == VK_CONTROL ||
						n == VK_MENU ||
						n == VK_PRIOR ||
						n == VK_NEXT) {
						if ((!IsItemHovered() && GetIO().MouseClicked[0])) {
							ClearActiveID();
							break;
						}
						if (GetAsyncKeyState(n) & 0x8000)
						{
							if (n == VK_HOME || n == VK_INSERT) {
								break;
							}

							if (n == VK_ESCAPE && bAllowNone) {
								ClearActiveID();
								output.m_Var = 0x0;
								break;
							}

							output.m_Var = n;
							ClearActiveID();
							break;
						}
					} //loop
				}
			}

			if (curr != prevv) {
				time = g_Interfaces.Engine->Time();
				prevv = curr;
			}

			GetCurrentContext()->ActiveIdAllowOverlap = true;
			if ((!IsItemHovered() && GetIO().MouseClicked[0]))
			{
				ClearActiveID();
			}
		}
		else if (Button(VK2STR(output.m_Var), ImVec2(100, 20))) {
			SetActiveID(id, GetCurrentWindow());
		}

		SameLine();
		TextUnformatted(label);
		PopID();

		return true;
	}

	/* Combobox with multiple selectable items */
	__inline void MultiCombo(std::vector<const char*> titles, std::vector<bool*> options, const std::string& description, std::string comboName) {
		if (titles.size() != options.size()) { return; }
		
		std::string preview = "<None>##";
		for (size_t i = 0; i < options.size(); i++) {
			if (*options[i]) {
				if (preview == "<None>##") { preview = ""; }
				preview += titles[i];
				preview.append(", ");
			}
		}
		preview.pop_back(); preview.pop_back(); // This is a stupid but easy way to remove the last comma

		PushItemWidth(150);
		PushStyleColor(ImGuiCol_Button, g_Menu.Accent.Value);
		PushStyleColor(ImGuiCol_ButtonHovered, g_Menu.AccentDark.Value);
		PushStyleColor(ImGuiCol_ButtonActive, g_Menu.AccentDark.Value);
		if (BeginCombo(comboName.c_str(), preview.c_str())) {
			PushStyleColor(ImGuiCol_Header, ImColor(40, 40, 40).Value);
			PushStyleColor(ImGuiCol_HeaderHovered, ImColor(50, 50, 50).Value);
			PushStyleColor(ImGuiCol_HeaderActive, ImColor(40, 40, 40).Value);
			for (size_t i = 0; i < titles.size(); i++) {
				Selectable((*options[i]) ? tfm::format("+ %s", titles[i]).c_str() : titles[i], options[i], ImGuiSelectableFlags_DontClosePopups);
			}
			PopStyleColor(3);

			EndCombo();
		}
		PopStyleColor(3);
		PopItemWidth();

		HelpMarker(description.c_str());
	}

	__inline bool ColorPicker(const char* label, Color_t& color)
	{
		bool open = false;
		ImVec4 tempColor = {};
		PushItemWidth(150);
		PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
		if (ColorEdit4(label, reinterpret_cast<float*>(&tempColor), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel)) {
			color = vColor(tempColor);
			open = true;
		}
		PopStyleVar();
		PopItemWidth();
		return open;
	}

	/* Inline color picker */
	__inline bool ColorPickerL(const char* label, Color_t& color, int num = 0)
	{
		SameLine(GetContentRegionMax().x - 20 - (num * 24));
		SetNextItemWidth(20);
		return ColorPicker(label, color);
	}

	__inline void TextCentered(const char* fmt)
	{
		const auto windowWidth = GetWindowSize().x;
		const auto textWidth = CalcTextSize(fmt).x;

		SetCursorPosX((windowWidth - textWidth) * 0.5f);
		Text(fmt);
	}

    // Source: https://github.com/ocornut/imgui/issues/1537#issuecomment-355569554
	__inline void ToggleButton(const char* str_id, bool* v)
    {
	    const auto p = GetCursorScreenPos();
        auto* drawList = GetWindowDrawList();
	    const auto style = GetStyle();

        const float height = GetFrameHeight();
        const float width = height * 1.8f;
        const float radius = height * 0.50f;
		const float bb_width = CalcItemWidth();
        const ImVec2 labelSize = CalcTextSize(str_id, nullptr, true);

        InvisibleButton(str_id, ImVec2(bb_width, height));
        if (IsItemClicked()) { *v = !*v; }

        float t = *v ? 1.0f : 0.0f;

        ImGuiContext& g = *GImGui;
        constexpr float ANIM_SPEED = 0.08f;
        if (g.LastActiveId == g.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
        {
	        const float tAnim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
            t = *v ? (tAnim) : (1.0f - tAnim);
        }

        const ImU32 colBg = IsItemHovered() ? ImColor(60, 60, 60) : ImColor(50, 50, 50);
        const ImU32 colCircle = (*v) ? g_Menu.Accent : ImColor(180, 180, 180);

        drawList->AddRectFilled(p, ImVec2(p.x + width, p.y + height), colBg, height * 0.5f);
        drawList->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, colCircle);
        drawList->AddText({ p.x + width + style.ItemInnerSpacing.x, p.y + (height / 2 - labelSize.y / 2) }, ImColor(255, 255, 255), str_id);
    }
}

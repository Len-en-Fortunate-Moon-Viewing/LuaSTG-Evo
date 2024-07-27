﻿#include "AppFrame.h"
// #include "utf8.hpp"
#include "utility/utf.hpp"
#include "uni_algo/ranges_grapheme.h"
#include <iterator>
#include <string>
#include <string_view>

namespace LuaSTGPlus
{
    // luastg plus interface
    
    constexpr int const TEXT_ALIGN_LEFT = 0x00;
    constexpr int const TEXT_ALIGN_CENTER = 0x01;
    constexpr int const TEXT_ALIGN_RIGHT = 0x02;

    constexpr int const TEXT_ALIGN_TOP = 0x00;
    constexpr int const TEXT_ALIGN_VCENTER = 0x04;
    constexpr int const TEXT_ALIGN_BOTTOM = 0x08;

    constexpr int const TEXT_FLAG_WORDBREAK = 0x10;

    // bool AppFrame::RenderText(IResourceFont* p, char* strBuf, Core::RectF rect, Core::Vector2F scale, FontAlignHorizontal halign, FontAlignVertical valign, bool bWordBreak)noexcept
    // {
    // 	using namespace Core;
    // 	using namespace Core::Graphics;

    // 	IGlyphManager* pGlyphManager = p->GetGlyphManager();
        
    // 	// 准备渲染字体
    // 	m_pTextRenderer->setGlyphManager(pGlyphManager);
    // 	m_pTextRenderer->setScale(scale);

    // 	// 设置混合和颜色
    // 	updateGraph2DBlendMode(p->GetBlendMode());
    // 	m_pTextRenderer->setColor(p->GetBlendColor());
        
    // 	// 第一次遍历计算要渲染多少行
    // 	const char* pText = strBuf;
    // 	int iLineCount = 1;
    // 	float fLineWidth = 0.f;
    // 	while (*pText)
    // 	{
    // 		bool bNewLine = false;
    // 		if (*pText == L'\n')
    // 			bNewLine = true;
    // 		else
    // 		{
    // 			GlyphInfo tGlyphInfo{};
    // 			if (pGlyphManager->getGlyph(*pText, &tGlyphInfo, true))
    // 			{
    // 				float adv = tGlyphInfo.advance.x * scale.x;
    // 				if (bWordBreak && fLineWidth + adv > std::abs(rect.a.x - rect.b.x))  // 截断模式
    // 				{
    // 					if (pText == strBuf || *(pText - 1) == L'\n')
    // 					{
    // 						++pText;  // 防止一个字符都不渲染导致死循环
    // 						if (*pText == L'\0')
    // 							break;
    // 					}
    // 					bNewLine = true;
    // 				}
    // 				else
    // 					fLineWidth += adv;
    // 			}
    // 		}
    // 		if (bNewLine)
    // 		{
    // 			++iLineCount;
    // 			fLineWidth = 0.f;
    // 		}
    // 		if (*pText != L'\0')
    // 			++pText;
    // 	}
        
    // 	// 计算起笔位置
    // 	float fTotalLineHeight = pGlyphManager->getLineHeight() * iLineCount * scale.y;
    // 	Core::Vector2F vRenderPos;
    // 	switch (valign)
    // 	{
    // 	case FontAlignVertical::Bottom:
    // 		vRenderPos.y = rect.b.y + fTotalLineHeight;
    // 		break;
    // 	case FontAlignVertical::Middle:
    // 		vRenderPos.y = rect.a.y - std::abs(rect.a.y - rect.b.y) / 2.f + fTotalLineHeight / 2.f;
    // 		break;
    // 	case FontAlignVertical::Top:
    // 	default:
    // 		vRenderPos.y = rect.a.y;
    // 		break;
    // 	}
    // 	vRenderPos.x = rect.a.x;
    // 	vRenderPos.y -= pGlyphManager->getAscender() * scale.y;
        
    // 	// 逐行渲染文字
    // 	char* pScanner = strBuf;
    // 	char c = 0;
    // 	bool bEOS = false;
    // 	fLineWidth = 0.f;
    // 	pText = pScanner;
    // 	while (!bEOS)
    // 	{
    // 		// 寻找断句位置，换行、EOF、或者行溢出
    // 		while (*pScanner != L'\0' && *pScanner != '\n')
    // 		{
    // 			GlyphInfo tGlyphInfo{};
    // 			if (pGlyphManager->getGlyph(*pScanner, &tGlyphInfo, true))
    // 			{
    // 				float adv = tGlyphInfo.advance.x * scale.x;

    // 				// 检查当前字符渲染后会不会导致行溢出
    // 				if (bWordBreak && fLineWidth + adv > std::abs(rect.a.x - rect.b.x))
    // 				{
    // 					if (pScanner == pText)  // 防止一个字符都不渲染导致死循环
    // 						++pScanner;
    // 					break;
    // 				}
    // 				fLineWidth += adv;
    // 			}
    // 			++pScanner;
    // 		}
            
    // 		// 在断句位置写入\0
    // 		c = *pScanner;
    // 		if (c == L'\0')
    // 			bEOS = true;
    // 		else
    // 			*pScanner = L'\0';
            
    // 		// 渲染从pText~pScanner的文字
    // 		std::string u8_str(pText);
    // 		Vector2F ignore_;
    // 		switch (halign)
    // 		{
    // 		case FontAlignHorizontal::Right:
    // 			m_pTextRenderer->drawText(u8_str, Vector2F(
    // 				vRenderPos.x + std::abs(rect.a.x - rect.b.x) - fLineWidth,
    // 				vRenderPos.y
    // 			), &ignore_);
    // 			break;
    // 		case FontAlignHorizontal::Center:
    // 			m_pTextRenderer->drawText(u8_str, Vector2F(
    // 				vRenderPos.x + std::abs(rect.a.x - rect.b.x) / 2.f - fLineWidth / 2.f,
    // 				vRenderPos.y
    // 			), &ignore_);
    // 			break;
    // 		case FontAlignHorizontal::Left:
    // 		default:
    // 			m_pTextRenderer->drawText(u8_str, vRenderPos, &ignore_);
    // 			break;
    // 		}

    // 		// 恢复断句处字符
    // 		*pScanner = c;
    // 		fLineWidth = 0.f;
    // 		if (c == L'\n')
    // 			pText = ++pScanner;
    // 		else
    // 			pText = pScanner;
            
    // 		// 移动y轴
    // 		vRenderPos.y -= pGlyphManager->getLineHeight() * scale.y;
    // 	}

    // 	return true;
    // }

    bool AppFrame::RenderText(IResourceFont* p, char* strBuf, Core::RectF rect, Core::Vector2F scale, FontAlignHorizontal halign, FontAlignVertical valign, bool bWordBreak)noexcept
    {
        using namespace Core;
        using namespace Core::Graphics;

        IGlyphManager* pGlyphManager = p->GetGlyphManager();
        std::string_view u8_str(strBuf);

        m_pTextRenderer->setGlyphManager(pGlyphManager);
        m_pTextRenderer->setScale(scale);

        updateGraph2DBlendMode(p->GetBlendMode());
        m_pTextRenderer->setColor(p->GetBlendColor());

        if (!pGlyphManager)
        {
            return false;
        }

        // First, cache all glyphs
        if (!pGlyphManager->cacheString(u8_str))
        {
            //return false; // Ignore unavailable glyphs
        }
        if (!pGlyphManager->flush())
        {
            return false;
        }
        
        int iLineCount = 1;
        float fLineWidth = 0.f;
        int iLineLength = 0;

        // Position parameters
        GlyphInfo glyph_info = {};
        float const line_height = pGlyphManager->getLineHeight() * scale.y; // Line height

        char32_t code_ = 0;
        utf::utf8reader reader_(u8_str.data(), u8_str.size());
        while (reader_(code_))
        {
            // newline processing
            bool bNewLine = false;
            if (code_ == U'\n')
                bNewLine = true;
            else if (pGlyphManager->getGlyph(code_, &glyph_info, true)) // 不要在这里 flush
            {
                float adv = glyph_info.advance.x * scale.x;

                if (bWordBreak && fLineWidth + adv > std::abs(rect.a.x - rect.b.x))
                {
                    bNewLine = true;
                }
                else
                {
                    fLineWidth += adv;
                    iLineLength = 0;
                }
            }
            if (bNewLine)
            {
                iLineCount += 1;
                fLineWidth = 0.f;
                iLineLength = 0;
            }
        }

        float fTotalLineHeight = pGlyphManager->getLineHeight() * iLineCount * scale.y;

        Core::Vector2F vRenderPos;
        switch (valign)
        {
        case FontAlignVertical::Bottom:
            vRenderPos.y = rect.b.y + fTotalLineHeight;
            break;
        case FontAlignVertical::Middle:
            vRenderPos.y = rect.a.y - std::abs(rect.a.y - rect.b.y) / 2.f + fTotalLineHeight / 2.f;
            break;
        case FontAlignVertical::Top:
        default:
            vRenderPos.y = rect.a.y;
            break;
        }
        vRenderPos.x = rect.a.x;
        vRenderPos.y -= pGlyphManager->getAscender() * scale.y;
        
        // Vector2F start_pos{ 0, 0 }; // Stroke position

        // // Spaces are common
        // GlyphInfo space_glyph_info = {};
        // if (!pGlyphManager->getGlyph(uint32_t(U' '), &space_glyph_info, true))
        // {
        //     //assert(false); return false; // Without a space, everything defaults to 0
        // }
        // space_glyph_info.advance.x *= scale.x;
        // space_glyph_info.advance.y *= scale.y;

        // std::string u8_str = std::string(strBuf);
        auto view = una::views::grapheme::utf8(u8_str);

        // Draw loop
        iLineLength = 0;
        fLineWidth = 0;
        int iCurrChar = 0;
        while (true)
        {

            char32_t code_ = 0;
            utf::utf8reader reader_(u8_str.data() + iCurrChar, u8_str.size() - iCurrChar);
            while (reader_(code_))
            {
                if (code_ == U'\n' || code_ == U'\0')
                    break;

                if (pGlyphManager->getGlyph(code_, &glyph_info, true)) // 不要在这里 flush
                {
                    float adv = glyph_info.advance.x * scale.x;

                    if (bWordBreak && fLineWidth + adv > std::abs(rect.a.x - rect.b.x))
                    {
                        if (iLineLength == 0)
                        {
                            fLineWidth += adv;
                            iLineLength += 1;
                        }
                        break;
                    }
                    fLineWidth += adv;
                    iLineLength += 1;
                }
            }

            std::string str(u8_str.substr(
                std::next(view.begin(), iCurrChar).begin() - u8_str.begin(),
                std::distance(std::next(view.begin(), iCurrChar).begin(), std::next(view.begin(), iCurrChar + iLineLength).begin())
            ));

            switch (halign)
            {
            case FontAlignHorizontal::Right:
                m_pTextRenderer->drawText(str, Vector2F(
                    vRenderPos.x + std::abs(rect.a.x - rect.b.x) - fLineWidth,
                    vRenderPos.y
                ), NULL);
                break;
            case FontAlignHorizontal::Center:
                m_pTextRenderer->drawText(str, Vector2F(
                    vRenderPos.x + std::abs(rect.a.x - rect.b.x) / 2.f - fLineWidth / 2.f,
                    vRenderPos.y
                ), NULL);
                break;
            case FontAlignHorizontal::Left:
            default:
                m_pTextRenderer->drawText(str, vRenderPos, NULL);
                break;
            }

            vRenderPos.y -= pGlyphManager->getLineHeight() * scale.y;

            iCurrChar += iLineLength;
            iLineLength = 0;
            fLineWidth = 0.f;

            if (code_ == U'\0' || iCurrChar > u8_str.length())
                break;

            if (code_ == U'\n')
                iCurrChar += 1;
        }

        return true;
    }

    Core::Vector2F AppFrame::CalcuTextSize(IResourceFont* p, const char* strBuf, Core::Vector2F scale)noexcept
    {
        using namespace Core;
        using namespace Core::Graphics;

        IGlyphManager* pGlyphManager = p->GetGlyphManager();
        
        int iLineCount = 1;
        float fLineWidth = 0.f;
        float fMaxLineWidth = 0.f;
        while (*strBuf)
        {
            if (*strBuf == L'\n')
            {
                ++iLineCount;
                fMaxLineWidth = std::max(fMaxLineWidth, fLineWidth);
                fLineWidth = 0.f;
            }
            else
            {
                GlyphInfo tGlyphInfo{};
                if (pGlyphManager->getGlyph(*strBuf, &tGlyphInfo, true))
                    fLineWidth += tGlyphInfo.advance.x * scale.x;
            }
            ++strBuf;
        }
        fMaxLineWidth = std::max(fMaxLineWidth, fLineWidth);
        
        return Core::Vector2F(fMaxLineWidth, iLineCount * pGlyphManager->getLineHeight() * scale.y);
    }
    
    bool AppFrame::RenderText(const char* name, const char* str, float x, float y, float scale, FontAlignHorizontal halign, FontAlignVertical valign)noexcept
    {
        Core::ScopeObject<IResourceFont> p = m_ResourceMgr.FindSpriteFont(name);
        if (!p)
        {
            spdlog::error("[luastg] RenderText: 找不到字体资源'{}'", name);
            return false;
        }
        
        // 编码转换
        std::string s_TempStringBuf;
        try
        {
            s_TempStringBuf = std::string(str);
        }
        catch (const std::bad_alloc&)
        {
            spdlog::error("[luastg] RenderText: 内存不足");
            return false;
        }
        
        // 计算渲染位置
        Core::Vector2F tSize = CalcuTextSize(p.get(), s_TempStringBuf.c_str(), Core::Vector2F(scale, scale));
        switch (halign)
        {
        case FontAlignHorizontal::Right:
            x -= tSize.x;
            break;
        case FontAlignHorizontal::Center:
            x -= tSize.x / 2.f;
            break;
        case FontAlignHorizontal::Left:
        default:
            break;
        }
        switch (valign)
        {
        case FontAlignVertical::Bottom:
            y += tSize.y;
            break;
        case FontAlignVertical::Middle:
            y += tSize.y / 2.f;
            break;
        case FontAlignVertical::Top:
        default:
            break;
        }
        
        return RenderText(
            p.get(),
            const_cast<char*>(s_TempStringBuf.data()),
            Core::RectF(x, y, x + tSize.x, y - tSize.y),
            Core::Vector2F(scale, scale),
            halign,
            valign,
            false
            );
    }
    
    bool AppFrame::RenderTTF(const char* name, const char* str,
        float left, float right, float bottom, float top, float scale, int format, Core::Color4B c)noexcept
    {
        Core::ScopeObject<IResourceFont> p = m_ResourceMgr.FindTTFFont(name);
        if (!p) {
            spdlog::error("[luastg] RenderTTF: Can't find font '{}'", name);
            return false;
        }
        
        // 编码转换
        std::string s_TempStringBuf;
        try {
            s_TempStringBuf = std::string(str);
        }
        catch (const std::bad_alloc&) {
            spdlog::error("[luastg] RenderTTF: Out of memory");
            return false;
        }
        
        // 计算格式
        bool bWordBreak = false;
        FontAlignHorizontal halign = FontAlignHorizontal::Left;
        FontAlignVertical valign = FontAlignVertical::Top;
        
        if ((format & TEXT_ALIGN_CENTER) == TEXT_ALIGN_CENTER)
            halign = FontAlignHorizontal::Center;
        else if ((format & TEXT_ALIGN_RIGHT) == TEXT_ALIGN_RIGHT)
            halign = FontAlignHorizontal::Right;
        
        if ((format & TEXT_ALIGN_VCENTER) == TEXT_ALIGN_VCENTER)
            valign = FontAlignVertical::Middle;
        else if ((format & TEXT_ALIGN_BOTTOM) == TEXT_ALIGN_BOTTOM)
            valign = FontAlignVertical::Bottom;
        
        if ((format & TEXT_FLAG_WORDBREAK) == TEXT_FLAG_WORDBREAK)
            bWordBreak = true;
        
        p->SetBlendColor(c);
        return RenderText(
            p.get(),
            const_cast<char*>(s_TempStringBuf.data()),
            Core::RectF(left, top, right, bottom),
            Core::Vector2F(scale, scale) * 0.5f,  // TODO: 缩放系数=0.5 ????????????
            halign,
            valign,
            bWordBreak
        );
    }
    
    // native interface
    
    bool AppFrame::FontRenderer_SetFontProvider(const char* name)
    {
        Core::ScopeObject<IResourceFont> p = m_ResourceMgr.FindTTFFont(name);
        if (!p)
        {
            spdlog::error("[luastg] SetFontProvider: Can't find font '{}'", name);
            return false;
        }
        m_pTextRenderer->setGlyphManager(p->GetGlyphManager());
        return true;
    }
    
    void AppFrame::FontRenderer_SetScale(Core::Vector2F const& s)
    {
        m_pTextRenderer->setScale(s);
    }
    
    Core::RectF AppFrame::FontRenderer_MeasureTextBoundary(const char* str, size_t len)
    {
        return m_pTextRenderer->getTextBoundary(Core::StringView(str, len));
    }
    
    Core::Vector2F AppFrame::FontRenderer_MeasureTextAdvance(const char* str, size_t len)
    {
        return m_pTextRenderer->getTextAdvance(Core::StringView(str, len));
    }
    
    bool AppFrame::FontRenderer_RenderText(const char* str, size_t len, Core::Vector2F& pos, const float z, const BlendMode blend, Core::Color4B const& color)
    {
        float const last_z = m_pTextRenderer->getZ();

        updateGraph2DBlendMode(blend);
        m_pTextRenderer->setZ(z);
        m_pTextRenderer->setColor(color);
        
        Core::Vector2F endpos;
        const bool result = m_pTextRenderer->drawText(Core::StringView(str, len), pos, &endpos);
        pos = endpos;

        m_pTextRenderer->setZ(last_z);
        return result;
    }
    
    bool AppFrame::FontRenderer_RenderTextInSpace(const char* str, size_t len, Core::Vector3F& pos, Core::Vector3F const& rvec, Core::Vector3F const& dvec, const BlendMode blend, Core::Color4B const& color)
    {
        updateGraph2DBlendMode(blend);
        m_pTextRenderer->setColor(color);

        Core::Vector3F endpos;
        const bool result = m_pTextRenderer->drawTextInSpace(
            Core::StringView(str, len),
            pos,
            rvec,
            dvec,
            &endpos);
        pos = endpos;

        return result;
    }

    float AppFrame::FontRenderer_GetFontLineHeight()
    {
        auto* p = m_pTextRenderer->getGlyphManager();
        if (p) return p->getLineHeight();
        return 0.0f;
    }
    
    float AppFrame::FontRenderer_GetFontAscender()
    {
        auto* p = m_pTextRenderer->getGlyphManager();
        if (p) return p->getAscender();
        return 0.0f;
    }
    
    float AppFrame::FontRenderer_GetFontDescender()
    {
        auto* p = m_pTextRenderer->getGlyphManager();
        if (p) return p->getDescender();
        return 0.0f;
    }
};

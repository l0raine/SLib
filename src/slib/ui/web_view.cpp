/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "slib/ui/web_view.h"

namespace slib
{
	
	SLIB_DEFINE_OBJECT(WebView, View)
	
	WebView::WebView()
	{
		setCreatingNativeWidget(sl_true);
		m_flagOfflineContent = sl_false;
	}
	
	WebView::~WebView()
	{
	}

	void WebView::loadURL(const String& url)
	{
		m_flagOfflineContent = sl_false;
		m_offlineContentHTML.setNull();
		m_urlOrigin = url;
		if (isNativeWidget()) {
			_load_NW();
		}
	}
	
	void WebView::loadHTML(const String& html, const String& baseURL)
	{
		m_flagOfflineContent = sl_true;
		m_offlineContentHTML = html;
		m_urlOrigin = baseURL;
		if (isNativeWidget()) {
			_load_NW();
		}
	}
	
	sl_bool WebView::isOfflineContent()
	{
		return m_flagOfflineContent;
	}
	
	String WebView::getOriginURL()
	{
		return m_urlOrigin;
	}
	
	String WebView::getURL()
	{
		if (isNativeWidget()) {
			return _getURL_NW();
		}
		return sl_null;
	}
	
	String WebView::getPageTitle()
	{
		if (isNativeWidget()) {
			return _getPageTitle_NW();
		}
		return sl_null;
	}
	
	void WebView::goBack()
	{
		if (isNativeWidget()) {
			_goBack_NW();
		}
	}
	
	void WebView::goForward()
	{
		if (isNativeWidget()) {
			_goForward_NW();
		}
	}
	
	void WebView::reload()
	{
		if (isNativeWidget()) {
			_reload_NW();
		}
	}
	
	void WebView::runJavaScript(const String& script)
	{
		if (isNativeWidget()) {
			_runJavaScript_NW(script);
		}
	}
	
	String WebView::getErrorMessage()
	{
		return m_lastErrorMessage;
	}
	
	void WebView::onStartLoad(const String& url)
	{
	}
	
	void WebView::onFinishLoad(const String& url, sl_bool flagFailed)
	{
	}
	
	void WebView::onMessageFromJavaScript(const String& msg, const String& param)
	{
	}
	
	void WebView::onResize(sl_ui_len width, sl_ui_len height)
	{
		if (isNativeWidget()) {
			_refreshSize_NW();
		}
	}
	
	void WebView::dispatchStartLoad(const String& url)
	{
		onStartLoad(url);
		getOnStartLoad()(this, url);
	}
	
	void WebView::dispatchFinishLoad(const String& url, sl_bool flagFailed)
	{
		onFinishLoad(url, flagFailed);
		getOnFinishLoad()(this, url, flagFailed);
	}
	
	void WebView::dispatchMessageFromJavaScript(const String& msg, const String& param)
	{
		onMessageFromJavaScript(msg, param);
		getOnMessageFromJavaScript()(this, msg, param);
	}
	
	
#if !(defined(SLIB_PLATFORM_IS_OSX)) && !(defined(SLIB_PLATFORM_IS_IOS)) && !(defined(SLIB_PLATFORM_IS_WIN32)) && !(defined(SLIB_PLATFORM_IS_ANDROID)) && !(defined(SLIB_PLATFORM_IS_TIZEN))
	
	Ref<ViewInstance> WebView::createNativeWidget(ViewInstance* parent)
	{
		return sl_null;
	}
	
	void WebView::_refreshSize_NW()
	{
	}
	
	void WebView::_load_NW()
	{
	}
	
	String WebView::_getURL_NW()
	{
		return sl_null;
	}
	
	String WebView::_getPageTitle_NW()
	{
		return sl_null;
	}
	
	void WebView::_goBack_NW()
	{
	}
	
	void WebView::_goForward_NW()
	{
	}
	
	void WebView::_reload_NW()
	{
	}
	
	void WebView::_runJavaScript_NW(const String& script)
	{
	}
	
#endif

}

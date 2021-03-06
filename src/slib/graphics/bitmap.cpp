/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "slib/graphics/bitmap.h"

#include "slib/graphics/image.h"
#include "slib/core/file.h"
#include "slib/core/asset.h"

namespace slib
{

	SLIB_DEFINE_OBJECT(BitmapCache, Object)

	BitmapCache::BitmapCache()
	{
	}

	BitmapCache::~BitmapCache()
	{
	}

	SLIB_DEFINE_OBJECT(Bitmap, Drawable)

	Bitmap::Bitmap()
	{
	}

	Bitmap::~Bitmap()
	{
	}

	Ref<Bitmap> Bitmap::create(const ImageDesc& desc)
	{
		Ref<Bitmap> ret = Bitmap::create(desc.width, desc.height);
		if (ret.isNotNull()) {
			ret->writePixels(0, 0, desc.width, desc.height, desc.colors, desc.stride);
			return ret;
		}
		return sl_null;
	}

	Ref<Bitmap> Bitmap::create(const Ref<Image>& image)
	{
		if (image.isNotNull()) {
			ImageDesc desc;
			image->getDesc(desc);
			return Bitmap::create(desc);
		}
		return sl_null;
	}

	Ref<Bitmap> Bitmap::loadFromMemory(const Memory& mem)
	{
		if (mem.isNotEmpty()) {
			return Bitmap::loadFromMemory(mem.getData(), mem.getSize());
		}
		return sl_null;
	}

	Ref<Bitmap> Bitmap::loadFromFile(const String& filePath)
	{
		Memory mem = File::readAllBytes(filePath);
		if (mem.isNotEmpty()) {
			return Bitmap::loadFromMemory(mem);
		}
		return sl_null;
	}

	Ref<Bitmap> Bitmap::loadFromAsset(const String& path)
	{
		Memory mem = Assets::readAllBytes(path);
		if (mem.isNotEmpty()) {
			return Bitmap::loadFromMemory(mem);
		}
		return sl_null;
	}

	sl_real Bitmap::getDrawableWidth()
	{
		return (sl_real)(getBitmapWidth());
	}

	sl_real Bitmap::getDrawableHeight()
	{
		return (sl_real)(getBitmapHeight());
	}

	sl_uint32 Bitmap::getWidth()
	{
		return getBitmapWidth();
	}

	sl_uint32 Bitmap::getHeight()
	{
		return getBitmapHeight();
	}

	sl_bool Bitmap::isEmpty()
	{
		return getBitmapWidth() == 0 || getBitmapHeight() == 0;
	}

	sl_bool Bitmap::isNotEmpty()
	{
		return getBitmapWidth() != 0 && getBitmapHeight() != 0;
	}

	void Bitmap::update(sl_uint32 x, sl_uint32 y, sl_uint32 width, sl_uint32 height)
	{
		m_drawableCached.setNull();
		{
			Ref<BitmapCache> cache = m_renderingTextureCached;
			if (cache.isNotNull()) {
				cache->update(x, y, width, height);
			}
		}
	}

	void Bitmap::update()
	{
		m_drawableCached.setNull();
		{
			Ref<BitmapCache> cache = m_renderingTextureCached;
			if (cache.isNotNull()) {
				cache->update(0, 0, getBitmapWidth(), getBitmapHeight());
			}		
		}
	}

	sl_bool Bitmap::readPixels(sl_uint32 x, sl_uint32 y, sl_uint32 width, sl_uint32 height, Color* colors, sl_int32 stride)
	{
		BitmapData bitmapData(width, height, colors, stride);
		return readPixels(x, y, bitmapData);
	}

	sl_bool Bitmap::writePixels(sl_uint32 x, sl_uint32 y, sl_uint32 width, sl_uint32 height, const Color* colors, sl_int32 stride)
	{
		BitmapData bitmapData(width, height, colors, stride);
		return writePixels(x, y, bitmapData);
	}

	sl_bool Bitmap::resetPixels(const Color& color)
	{
		return resetPixels(0, 0, getWidth(), getHeight(), color);
	}

}

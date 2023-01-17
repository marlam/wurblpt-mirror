/*
 * Copyright (C) 2019, 2020, 2021, 2022
 * Computer Graphics Group, University of Siegen (written by Martin Lambers)
 * Copyright (C) 2022, 2023
 * Martin Lambers <marlam@marlam.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "material.hpp"


namespace WurblPT {

class LightDiffuse final : public Material
{
private:
    const vec4 _emit;
    const Texture* _tex;

public:
    LightDiffuse(const vec4& emit, const Texture* tex = nullptr) :
        _emit(emit), _tex(tex)
    {
    }

    LightDiffuse(const vec3& emit, const Texture* tex = nullptr) :
        _emit(emit, average(emit)), _tex(tex)
    {
    }

    virtual vec4 emitted(const Ray& ray, const HitRecord& hit) const override
    {
        vec4 e(0.0f);
        if (!hit.backside) {
            e = _emit;
            if (_tex) {
                vec3 rgb = _tex->value(hit.texcoords, ray.time).rgb();
                e *= vec4(rgb, average(rgb));
            }
        }
        return e;
    }

    virtual void exportToMtl(
            ObjMaterial& objMaterial,
            std::ostream& geometryOut, std::ostream& materialOut,
            unsigned int& globalVertexIndex,
            AnimationCache& animationCache,
            const std::filesystem::path& basePath, const std::string& baseName,
            std::map<const SceneComponent*, std::string>& sceneExportCache) const override
    {
        objMaterial.Ke = _emit.rgb();
        if (_tex) {
            objMaterial.map_Ke = _tex->exportToObj(geometryOut, materialOut, globalVertexIndex, false, animationCache, basePath, baseName, sceneExportCache);
        }
    }
};

}

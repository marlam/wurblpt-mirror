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

#include <tgd/array.hpp>

#include "hitable.hpp"
#include "ray.hpp"


namespace WurblPT {

class Sensor
{
public:
    constexpr static int maxPixelComponents = 3;

    /* Interface used by the mcpt() function: */

    virtual unsigned int width() const
    {
        return 0;
    };

    virtual unsigned int height() const
    {
        return 0;
    };

    virtual void accumulateRadiance(
            const Ray& /* r */,
            unsigned int /* pathComponent */,
            float /* geometricPathLength */,            // might be 0 if unknown, e.g. for environment map
            const vec4& /* opticalPathLength */,        // might be 0 if unknown, e.g. for environment map
            const vec4& /* radiance */,
            const HitRecord& /* hitRecord */,           // hitRecord.haveHit might be false, e.g. for an env map
            float /* t0 */, float /* t1 */,
            float* /* sampleAccumulator */) const
    {
    }

    virtual void finishPixel(unsigned int /* pixelIndex */, float /* invSamples */,
            const float* /* sampleAccumulator */)
    {
    }

    virtual TGD::ArrayContainer* pixelArray()
    {
        return nullptr;
    }

    /* Other functions: */

    virtual float aspectRatio() const
    {
        return float(width()) / height();
    }
};

}

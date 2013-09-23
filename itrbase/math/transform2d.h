/*
 *
 *   Copyright (C) 2013 BUAA iTR Research Center. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * transform2d.h
 *  Created on: 2013-9-23
 *      Author: buaa
 */

#ifndef TRANSFORM2D_H_
#define TRANSFORM2D_H_

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{

    class Transform2D
    {
        public:
            Transform2D();
            virtual ~Transform2D();
            inline Matrix& GetTransformMatrix()
            {
                return transformMatrix;
            }
            void Reset();
            void Offset(F32 X,F32 Y);
            void Scale(F32 K);
            void Rotate(F32 Angle);

            Vector operator*(const Vector& Vec) const
            {
                Vector v(2);
                return v;
            }
        private:
            Matrix transformMatrix;
            Matrix tempMatrix;
            Vector inputVector;

    };

} // namespace itr_math
#endif // TRANSFORM2D_H_

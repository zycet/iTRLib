#ifndef CONVERTFORMAT_H
#define CONVERTFORMAT_H

#include "itrbase.h"
#include "../image/image.h"

using itr_math::Matrix;

namespace itr_vision
{
    class ConvertFormat
    {
        public:
            static void ImageARGB2Matrix(const ImageARGB &input,Matrix &output);
            static void ImageGray2Matrix(const ImageGray &input,Matrix &output);
            static void Matrix2ImageARGB(const Matrix &input, ImageARGB& output);
            static void Matrix2ImageGray(const Matrix &input, ImageGray& output);
        protected:
        private:
    };
}
#endif // CONVERTFORMAT_H

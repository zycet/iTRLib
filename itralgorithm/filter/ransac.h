#ifndef RANSAC_H
#define RANSAC_H

namespace itr_algorithm
{
    class Ransac
    {
        public:
            /** Default constructor */
            Ransac();
            static void Process(S32 count, F32 *x, S32 &drop);
        protected:
        private:
    };

    abstract class Operator
    {
        public:
        virtual F32 GetError(F32 a, F32 b);
        virtual F32 GetValue(F32 *data, S32 N);
        virtual bool Remain(F32 error);
    }
}
#endif // RANSAC_H

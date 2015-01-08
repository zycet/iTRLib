#ifndef ITRTHREAD_H
#define ITRTHREAD_H

namespace itr_system
{
    class iTRThread
    {
        public:
            /** Default constructor */
            iTRThread();
            /** Default destructor */
            virtual ~iTRThread(){pthread_exit(NULL);}

            virtual void* Do(void *){}

            void Start()
            {
                pthread_create(&tid, NULL, Do, NULL);
            }
        protected:
        private:
        pthread_t tid;

    };
}
#endif // ITRTHREAD_H

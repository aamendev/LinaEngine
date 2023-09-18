namespace Lina{ namespace Math{
    class Random
    {
        private:
            ulong u,v,w;
        public:
            Random(ulong j): v(4101842887655102017LL), w(1)
        {
            u = j ^ v; int64();
            v = u; int64();
            w = v; int64();
        }
            friend std::ostream operator<<(std::ostream& os, const Random& r);
            inline ulong int64()
            {
                u = u * 2862933555777941757LL + 7046029254386353087LL;
                v ^= v >> 17; v ^= v << 31; v ^= v >> 8;
                w = 4294957665U*(w & 0xffffffff) + (w >> 32);
                ulong x = u ^ (u << 21); x ^= x >> 35; x ^= x << 4;
                return (x + v) ^ w;
            }
    };
}}

#include <algorithm>
#include <cmath>

class Collision {

public:
    //Expects angles in degrees
    static inline bool IsColliding(Collider *colA, Collider *colB, float angleOfA, float angleOfB) {
        Rect a = colA->GetAssociatedBox(), b = colB->GetAssociatedBox();
        Vec2 A[] = { Vec2( a.x, a.y + a.h ),
                     Vec2( a.x + a.w, a.y + a.h ),
                     Vec2( a.x + a.w, a.y ),
                     Vec2( a.x, a.y )
        };
        Vec2 B[] = { Vec2( b.x, b.y + b.h ),
                     Vec2( b.x + b.w, b.y + b.h ),
                     Vec2( b.x + b.w, b.y ),
                     Vec2( b.x, b.y )
        };

        for (auto& v : A) {
            v = RotateDeg(v - a.GetCenter(), angleOfA) + a.GetCenter();
        }

        for (auto& v : B) {
            v = RotateDeg(v - b.GetCenter(), angleOfB) + b.GetCenter();
        }

        Vec2 axes[] = { Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2]) };

        bool right = false, left = false, top = false, bottom = false;

        for (auto& axis : axes) {
            float P[4];

            for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

            float minA = *std::min_element(P, P + 4);
            float maxA = *std::max_element(P, P + 4);

            for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

            float minB = *std::min_element(P, P + 4);
            float maxB = *std::max_element(P, P + 4);

            if (maxA < minB || minA > maxB){
                colA->SetEdge(Edge(right, left, top, bottom));
                return false;
            }
        }

        auto dx = (a.x + a.w/2) - (b.x + b.w/2);
        auto dy = (a.y + a.h/2) - (b.y + b.h/2);
        auto width = (a.w + b.w)/2;
        auto height = (a.h + b.h)/2;
        auto crossWidth = width * dy;
        auto crossHeight = height * dx;

        if(abs(dx) <= width && abs(dy) <= height){
            if(crossWidth>crossHeight){
                if(crossWidth > -crossHeight){
                    bottom = true;
                    left = false;
                } else{
                    left = true;
                    bottom = false;
                }
            }else{
                if(crossWidth > -crossHeight){
                    right = true;
                    top = false;
                } else{
                    top = true;
                    right = false;
                }
            }
        }

        colA->SetEdge(Edge(right, left, top, bottom));

        return true;
    }

private:

    static inline float Mag(const Vec2& p) {
        return std::sqrt(p.x * p.x + p.y * p.y);
    }

    static inline Vec2 Norm(const Vec2& p) {
        return p * (1.f / Mag(p));
    }

    static inline float Dot(const Vec2& a, const Vec2& b) {
        return a.x * b.x + a.y * b.y;
    }

    static inline Vec2 RotateDeg(const Vec2& p, float angleDeg) {
        auto angle = angleDeg * M_PI/180;
        float cs = cos(angle), sn = sin(angle);
        return Vec2 ( p.x * cs - p.y * sn, p.x * sn + p.y * cs );
    }
};

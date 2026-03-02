#include "filterwithmatrix.h"

const int64_t CHANGER = 10;

class MyFilter : public FilterWithMatrix {
public:
    MyFilter() : FilterWithMatrix({{-1, 1, -1}, {1, CHANGER, 1}, {-1, 1, -1}}) {
    }
    Image Change(Image& image) override;
};

#include "Line.h"

ostream& operator<<(ostream& out, Line const& l){
    l.display(out);
    return out;
}

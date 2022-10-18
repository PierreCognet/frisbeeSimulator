#include "Cone.h"

ostream& operator<<(ostream& out, Cone const& c){
    c.display(out);
    return out;
}

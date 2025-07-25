#include "Observer.h"
#include "Window.h"
#include "Subject.h"

class GraphicsDisplay : public Observer {
    Xwindow xw;
    int size;
    public:
        static inline const int window_size=500;
        static inline const int board_size=400;
        static inline const int edge_size=50;
        GraphicsDisplay(int n);
        void virtual notify(Subject &who) override;
};

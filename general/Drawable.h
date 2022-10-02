#ifndef PRJ_DRAWABLE_H
#define PRJ_DRAWABLE_H

class Canvas;


class Drawable {

public:
	
	Drawable(Canvas* canvas)
		: canvas_(canvas)	{}
	
	virtual ~Drawable() {}
		
	Canvas* canvas() const { return canvas_; }

	virtual void draw() const = 0;


protected:

	Canvas* canvas_;
};

#endif

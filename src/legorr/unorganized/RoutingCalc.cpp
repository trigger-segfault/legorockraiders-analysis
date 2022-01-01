
void __cdecl Routing_Maths_Vector2D_FUN_00406520(Point2F *out_point,Point2F *a,Point2F *b,Point2F *c,Point2F *d,float scalar)
{
	float fVar1;
	float fVar2;
	float fVar3;
	float fVar4;
	float fVar5;
	float fVar6;
	
	float xVar0 = a->x + (b->x*3.0);

	float xVar1 = (xVar0 - a->x) * 3.0;
	float xVar1 = ((a->x+(b->x*3.0)) - a->x) * 3.0;
	// (simplified)
	float xVar1 = (b->x * 3.0) * 3.0; // * 9.0

	float xVar2 = ((c->x - (d->x * 3.0)) - xVar0) * 3.0 - xVar1;
	float xVar2 = (((c->x-(d->x*3.0)) - (a->x+(b->x*3.0))) * 3.0) - (b->x * 3.0 * 3.0);
	//float xVar2 = ((c->x - (d->x * 3.0)) - (b->x * 3.0) + a->x) * 3.0 - xVar1;
	
	float fVar1 = (b->x * 3.0) + a->x;
	float scalarSqr = scalar * scalar;
	fVar4 = (fVar1 - a->x) * 3.0;
	xVar2 = ((c->x - (d->x * 3.0)) - fVar1) * 3.0 - fVar4;
	fVar1 = d->y;
	fVar6 = a->y + (b->y * 3.0);
	fVar2 = c->y;

	//float scalar = scalar;
	float scalarSqr = scalar * scalar;
	float scalarCbe = scalar * scalar * scalar;

	out_point->x = a->x + ((xVar1)*scalar) + ((xVar2)*scalarSqr) + ((((c->x-a->x) - xVar1) - xVar2)*scalarCbe);

	// out_point->x = (xVar1 * scalar) + (xVar2 * scalarSqr) + ((((c->x - a->x) - xVar1) - xVar2) * scalarCbe) + a->x;

	float yVar0 = a->y + (b->y*3.0);
	//float yVar1 = (((c->x-(d->x*3.0)) - (a->x+(b->x*3.0))) * 3.0) - (b->x * 3.0 * 3.0);

	float yVar01 = ((a->y+(b->y*3.0)) - a->y) * 3.0;
	float yVar1 = (yVar0-a->y) * 3.0;
	float yVar1 = ((a->y + (b->y * 3.0)) - a->y) * 3.0;
	// simplified
	float yVar1 = (b->y * 3.0 * 3.0);
	float yVar2 = ((c->y-(d->y*3.0)) - yVar0) * 3.0 - yVar1;

	out_point->y = a->y + ((yVar1)*scalar) + ((yVar2)*scalarSqr) + ((((c->y-a->y) - yVar1) - yVar2)*scalarCbe);

	// out_point->y = a->y + (yVar1*scalar) + (yVar2*scalarSqr) + ((((c->y-a->y) - yVar1) - yVar2)*scalarCbe);
	
	// out_point->y = (yVar2 * scalarSqr) + (fVar3 * scalar) + ((((c->y - a->y) - fVar3) - fVar1) * scalarCbe) + a->y;
	


	//
	out_point->x = fVar4 * scalar +
								 fVar3 * scalarSqr + (((c->x - a->x) - fVar4) - fVar3) * scalarSqr * scalar +
								 a->x;

	float fVar3 = ((a->y + (b->y * 3.0)) - a->y) * 3.0;
	// simplified
	float fVar3 = (b->y * 3.0) * 3.0;
	float fVar1 = ((c->y - d->y * 3.0) - fVar6) * 3.0 - fVar3;
	out_point->y = fVar1 * scalarSqr +
								 fVar3 * scalar + (((c->y - a->y) - fVar3) - fVar1) * scalarSqr * scalar +
								 a->y;
	return;
}


float Maths_InterpolationDelta(float start, float end, float current)
	{ return (current - start) / (end - start); }
float Maths_Interpolate(float start, float end, float delta)
	{ return start + ((end - start) * delta); }





uint __cdecl Routing_Calculate_FUN_004067f0(RoutingData *route,float currentDist,Point2F *out_r)
{
	uint loop;
	float endDist = 0.0;
	for (loop = 1; loop < route->count; loop++) {
		endDist += route->distances[loop]
		if (endDist > currentDist)
			break;
	}
	/*for (loop = 1;
		(loop < route->count && (endDist += route->distances[loop], endDist <= currentDist))
		; loop++) {
	}*/
	if (loop < route->count) {
		// assignment has no effect
		//out_r->x = route->points[loop-1].x;
		//out_r->y = route->points[loop-1].y;
		*out_r = route->points[loop-1];

		//float Maths_InterpolationDelta(float start, float end, float current)
		//	{ return (current - start) / (end - start); }
		// current = currentDist
		// start   = (endDist - route->distances[loop])
		// end     = endDist
		float delta = Maths_InterpolationDelta((endDist - route->distances[loop]), endDist, currentDist);
		out_r->x = Maths_Interpolate(route->points[loop-1].x, route->points[loop].x, delta);
		out_r->y = Maths_Interpolate(route->points[loop-1].y, route->points[loop].y, delta);

		//float delta = (currentDist - (endDist - route->distances[loop])) / route->distances[loop];
		//out_r->x = route->points[loop-1].x + ((route->points[loop].x - route->points[loop-1].x) * delta);
		//out_r->y = route->points[loop-1].y + ((route->points[loop].y - route->points[loop-1].y) * delta);
	}
	else {
		//out_r->x = route->points[loop-1].x;
		//out_r->y = route->points[loop-1].y;
		*out_r = route->points[loop-1];
	}
	return loop;


	float fVar1;
	float fVar2;
	float fVar3;
	uint index;
	float *pfVar4;
	uint count;
	
	fVar3 = 0.0;
	count = route->count;
	index = 1;
	if (1 < count) {
		pfVar4 = route->distances;
		do {
			pfVar4 = pfVar4 + 1;
			fVar3 = fVar3 + *pfVar4;
			if (currentDist < fVar3) break;
			index += 1;
		} while (index < count);
	}
	if (index < count) {
		out_point->x = route->points[index - 1].x;
		out_point->y = route->points[index - 1].y;
		fVar1 = route->points[index].y;
		fVar2 = route->points[index - 1].y;
		fVar3 = (currentDist - (fVar3 - route->distances[index])) / route->distances[index];
		out_point->x = (route->points[index].x - route->points[index - 1].x) * fVar3 +
									 route->points[index - 1].x;
		out_point->y = (fVar1 - fVar2) * fVar3 + route->points[index - 1].y;
		return index;
	}
	out_point->x = route->points[index - 1].x;
	out_point->y = route->points[index - 1].y;
	return index;
}

def calc1(p1, p2, p3, p4, t):
	p1,p2,p3,p4,t = float(p1),float(p2),float(p3),float(p4),float(t)#(1.0 - float(t))
	t2 = t * t      # sqr(t)
	t3 = t * t * t  # cbe(t)
	return t3*p4 + (3.0*t2 - 3.0*t3)*p3 + (3.0*t3 - 6*t2 + 3.0*t)*p2 + (3.0*t2 - t3 - 3.0*t + 1.0)*p1

def calc0(p1, p2, p3, p4, t):
	p1,p2,p3,p4,t = float(p1),float(p2),float(p3),float(p4),float(t)#(1.0 - float(t))
	t2 = t * t
	t3 = t * t * t
	#
	A = (3.0*t2 - 3.0*t3)
	B = (3.0*t3 - 6.0*t2 + 3.0*t)
	C = (3.0*t2 - t3 - 3.0*t + 1.0)
	#
	return t3*p4 + A*p3 + B*p2 + C*p1

def Cube(t): return t*t*t

def Square(t): return t*t

def calce(p0, p1, p2, p3, t):
	return Cube(1 - t) * p0 + 3.0 * Square(1 - t) * t * p1 + 3.0 * (1 - t) * Square(t) * p2 + Cube(t) * p3

def calcd(p0, p1, p2, p3, t):
	return 3.0 * Square(1 - t) * (p1 - p0) + 6.0 * (1 - t) * t * (p2 - p1) + 3.0 * Square(t) * (p3 - p2)

# input parameters: p1, p2, p3, p4, t [0.0-1.0]
# output parameter: r
def calc2(p1, p2, p3, p4, t):
	p1,p2,p3,p4,t = float(p1),float(p2),float(p3),float(p4),float(t)
	t2 = t * t      # sqr(t)
	t3 = t * t * t  # cbe(t)
	#
	pVar0 = p1 + (p2*3.0)
	#
	pVar1 = (pVar0-p1) * 3.0
	#
	pVar2 = ((p3-(p4*3.0)) - pVar0) * 3.0 - pVar1
	#
	return p1 + ((pVar1)*t) + ((pVar2)*t2) + (((p3-p1) - pVar1 - pVar2)*t3)

ps = (1.0, 3.0, 2.1, 3.0, 0.7)
calc1(*ps)
calc2(*ps)



def getPt(n1, n2, perc):
	n1,n2,perc = float(n1),float(n2),float(perc)
	diff = n2 - n1
	#
	return n1 + ( diff * perc )

def calc3(p1, p2, p3, p4, t):
	x1,x2,x3,x4,t = float(p1),float(p2),float(p3),float(p4),float(t)
	#
	def getPt(n1, n2, perc):
		n1,n2,perc = float(n1),float(n2),float(perc)
		diff = n2 - n1
		#
		return n1 + ( diff * perc )
	#
	for ii in range(50):
		i = 0.02 * ii
		# The Green Line
		xa = getPt( x1 , x2 , i )
		xb = getPt( x2 , x3 , i )
		# The Black Dot
		x = getPt( xa , xb , i )
		return x

def calc4(P0,P1,P2,P3,t):
	return pow((1-t),3) *P0 + 3*t*pow((1-t),2)*P1 + 3*pow((t),2)*(1-t)*P2 + pow((t),3)*P3


for ii in range(50):
	i = 0.02 * ii
    # The Green Line
    xa = getPt( x1 , x2 , i )
    ya = getPt( y1 , y2 , i )
    xb = getPt( x2 , x3 , i )
    yb = getPt( y2 , y3 , i )
	# The Black Dot
    x = getPt( xa , xb , i )
    y = getPt( ya , yb , i )
	return x,y

def formCRCurve(points: p1, p2, p3, p4):
	d_start = vector(p2.x - p1.x, p2.y - p1.y)
	d_end = vector(p4.x - p3.x, p4.y - p3.y)
	return Curve(p2, d_start, d_end, p3)


def other():
	i = 0
	e = points.length-4
	bcurves = []
	do {
		pointset = points.subset(i, 4)
		bcurves.push(formBezierCurve(pointset))
	} while(i++<e)

def formBezierCurve(points: p1, p2, p3, p4):
	return bezier(
		p2,
		p2 + (p3 - p1)/6
		p3 - (p4 - p2)/6
		p3
	)


class Spline:
	points:


def spline_at(t:float, points:list, D:int):
    if(points.size() < 4) {
      return T();
    }
    if(t > 0.999f) {
      t = 0.99f;
    }
    else if(t < 0) {
      t = 0;
    }

    T result;

    // get local "t" (also mu)	
    float curve_p = t * (points.size()-1);
    int curve_num = curve_p;
    t = curve_p - curve_num; // local t
	
    // get the 4 points
    int b = curve_num;
    int a = b - 1;
    int c = b + 1;
    int d = c + 1;
    if(a < 0) {
      a = 0;
    }
    if(d >= points.size()) {
      d = points.size()-1;
    }
	
    T& p0 = points[a]; // a
    T& p1 = points[b]; // b 
    T& p2 = points[c]; // c
    T& p3 = points[d]; // d 

	
    float t2 = t*t;
    float t3 = t*t*t;

    for i in range(D):
      result[i] = 0.5 * ((2 * p1[i]) + (-p0[i] + p2[i]) * t + (2 * p0[i] - 5 * p1[i] + 4 * p2[i] - p3[i]) * t2 + (-p0[i] + 3 * p1[i] - 3 * p2[i] + p3[i]) * t3);
    }

    return result;

def calc3(p0, p1, p2, p3, t, a):
	p0,p1,p2,p3,t = float(p0),float(p1),float(p2),float(p3),float(t),float(a)
float t0 = 0.0f;
float t1 = t0 + pow(distance(p0, p1), alpha);
float t2 = t1 + pow(distance(p1, p2), alpha);
float t3 = t2 + pow(distance(p2, p3), alpha);

vec2 m1 = (1.0f - tension) * (t2 - t1) *
    ((p1 - p0) / (t1 - t0) - (p2 - p0) / (t2 - t0) + (p2 - p1) / (t2 - t1));
vec2 m2 = (1.0f - tension) * (t2 - t1) *
    ((p2 - p1) / (t2 - t1) - (p3 - p1) / (t3 - t1) + (p3 - p2) / (t3 - t2));


float t01 = pow(distance(p0, p1), alpha);
float t12 = pow(distance(p1, p2), alpha);
float t23 = pow(distance(p2, p3), alpha);

vec2 m1 = (1.0f - tension) *
    (p2 - p1 + t12 * ((p1 - p0) / t01 - (p2 - p0) / (t01 + t12)));
vec2 m2 = (1.0f - tension) *
    (p2 - p1 + t12 * ((p3 - p2) / t23 - (p3 - p1) / (t12 + t23)));

Segment segment;
segment.a = 2.0f * (p1 - p2) + m1 + m2;
segment.b = -3.0f * (p1 - p2) - m1 - m1 - m2;
segment.c = m1;
segment.d = p1;

for( float i = 0 ; i < 1 ; i += 0.01 )
{
    // The Green Line
    xa = getPt( x1 , x2 , i );
    ya = getPt( y1 , y2 , i );
    xb = getPt( x2 , x3 , i );
    yb = getPt( y2 , y3 , i );

    // The Black Dot
    x = getPt( xa , xb , i );
    y = getPt( ya , yb , i );

    drawPixel( x , y , COLOR_RED );
}

inline float BezierCurve_Cubic1(float p1, float p2, float p3, float p4, float t)
{
	float t2 = t * t;     // sqr(t)
	float t3 = t * t * t; // cbe(t)
	return t3*p4 + (3*t2 - 3*t3)*p3 + (3*t3 - 6*t2 + 3*t)*p2 + (3*t2 - t3 - 3*t + 1)*pt1;
}


// input parameters: p1, p2, p3, p4, t [0.0-1.0]
// output parameter: r
void __cdecl Routing_Math1(float p1, float p2, float p3, float p4, float t)
{
	float t2 = t * t;     // sqr(t)
	float t3 = t * t * t; // cbe(t)
	
	float pVar0 = p1 + (p2*3.0);
	
	float pVar1 = (pVar0-p1) * 3.0;
	
	float pVar2 = ((p3-(p4*3.0)) - pVar0) * 3.0 - pVar1;
	
	// result
	return p1 + ((pVar1)*t) + ((pVar2)*t2) + (((p3-p1) - pVar1 - pVar2)*t3);
}

// input parameters: p1, p2, p3, p4, t [0.0-1.0]
// output parameter: r
void __cdecl Routing_Maths_Vector2D_FUN_00406520(OUT Point2F *r,Point2F *p1,Point2F *p2,Point2F *p3,Point2F *p4,float t)
{
	//float scalar1 = t;
	float t2 = t * t;     // sqr(t)
	float t3 = t * t * t; // cbe(t)

	float xVar0 = p1->x + (p2->x*3.0);
	float yVar0 = p1->y + (p2->y*3.0);

	float xVar1 = (xVar0-p1->x) * 3.0;
	float yVar1 = (yVar0-p1->y) * 3.0;

	float xVar2 = ((p3->x-(p4->x*3.0)) - xVar0) * 3.0 - xVar1;
	float yVar2 = ((p3->y-(p4->y*3.0)) - yVar0) * 3.0 - yVar1;

	// inlined1
	float xVar1 = ((p1->x+(p2->x*3.0))-p1->x) * 3.0;
	float yVar1 = ((p1->y+(p2->y*3.0))-p1->y) * 3.0;

	float xVar2 = ((p3->x-(p4->x*3.0)) - (p1->x+(p2->x*3.0))) * 3.0 - xVar1;
	float yVar2 = ((p3->y-(p4->y*3.0)) - (p1->y+(p2->y*3.0))) * 3.0 - yVar1;

	// inlined2 + simplified
	float xVar1 = ((p1->x+(p2->x*3.0))-p1->x) * 3.0;
	float yVar1 = ((p1->y+(p2->y*3.0))-p1->y) * 3.0;

	float xVar2 = (((p3->x-(p4->x*3.0)) - (p1->x+(p2->x*3.0))) * 3.0) - ((xVar0-p1->x) * 3.0);
	float yVar2 = (((p3->y-(p4->y*3.0)) - (p1->y+(p2->y*3.0))) * 3.0) - ((yVar0-p1->y) * 3.0);

	// inlined3 + simplified
	float xVar1 = p2->x*3.0*3.0;
	float yVar1 = p2->y*3.0*3.0;

	// distance: (((p3 dist p4*3) - (p1 dist p2*3))*3) - (p2*3*3)

	// inlined4
	float xVar2 = (((p3->x-(p4->x*3.0)) - (p1->x+(p2->x*3.0))) * 3.0) - ((xVar0-p1->x) * 3.0);
	float yVar2 = (((p3->y-(p4->y*3.0)) - (p1->y+(p2->y*3.0))) * 3.0) - ((yVar0-p1->y) * 3.0);

	// inlined5
	float xVar2 = (((p3->x-(p4->x*3.0)) - (p1->x+(p2->x*3.0))) * 3.0) - (p2->x*3.0*3.0);
	float yVar2 = (((p3->y-(p4->y*3.0)) - (p1->y+(p2->y*3.0))) * 3.0) - (p2->y*3.0*3.0);
	
	// inlined5 + simplified
	float xVar2 = (((p3->x-(p4->x*3.0)) - (p1->x+(p2->x*3.0))) - (p2->x*3.0)) * 3.0;
	float yVar2 = (((p3->y-(p4->y*3.0)) - (p1->y+(p2->y*3.0))) - (p2->x*3.0)) * 3.0;

	
	float Maths_InterpolationDelta(float start, float end, float current)
		{ return (current - start) / (end - start); }
	float Maths_Interpolate(float start, float end, float delta)
		{ return start + ((end - start) * delta); }

	Maths_Interpolate( (p3->x-(p4->x*3.0)), (p1->x+(p2->x*3.0)), 3.0 );

	// inlined6 + simplified
	float xVar2 = (((p3->x-(p4->x*3.0)) - (p1->x+(p2->x*3.0))) - (p2->x*3.0)) * 3.0;
	float yVar2 = (((p3->y-(p4->y*3.0)) - (p1->y+(p2->y*3.0))) - (p2->x*3.0)) * 3.0;

	// result
	r->x = p1->x + ((xVar1)*t) + ((xVar2)*t2) + (((p3->x-p1->x) - xVar1 - xVar2)*t3);
	r->y = p1->y + ((yVar1)*t) + ((yVar2)*t2) + (((p3->y-p1->y) - yVar1 - yVar2)*t3);
	

	// inlined1
	r->x = p1->x + ((p2->x*3.0*3.0)*t) + ((xVar2)*t2) + (((p3->x-p1->x) - xVar1 - xVar2)*t3);
	r->y = p1->y + ((p2->y*3.0*3.0)*t) + ((yVar2)*t2) + (((p3->y-p1->y) - yVar1 - yVar2)*t3);

	// inlined2
	r->x = p1->x + ((p2->x*3.0*3.0)*t) + ((xVar2)*t2) + (((p3->x-p1->x) - (p2->x*3.0*3.0) - xVar2)*t3);
	r->y = p1->y + ((p2->y*3.0*3.0)*t) + ((yVar2)*t2) + (((p3->y-p1->y) - (p2->y*3.0*3.0) - yVar2)*t3);


	//Generalized code, not C++
	//variables passed to function:   t,  x1, y1, x2, y2, x3, y3, x4, y4
	//variables declared in function: t2, t3, x,  y
	t2 = t * t
	t3 = t * t * t
	x = t3*x4 + (3*t2 - 3*t3)*x3 + (3*t3 - 6*t2 + 3*t)*x2 + (3*t2 - t3 - 3*t + 1)*x1
	y = t3*y4 + (3*t2 - 3*t3)*y3 + (3*t3 - 6*t2 + 3*t)*y2 + (3*t2 - t3 - 3*t + 1)*y1

	x = t3*x4 + (3*t2 - 3*t3)*x3 + (3*t3 - 6*t2 + 3*t)*x2 + (3*t2 - t3 - 3*t + 1)*x1
	y = t3*y4 + (3*t2 - 3*t3)*y3 + (3*t3 - 6*t2 + 3*t)*y2 + (3*t2 - t3 - 3*t + 1)*y1

	// https://stackoverflow.com/p1/67766611/7517185
	t2 = t * t
	t3 = t * t * t

	A = (3*t2 - 3*t3)
	B = (3*t3 - 6*t2 + 3*t)
	C = (3*t2 - t3 - 3*t + 1)

	x = t3*x4 + A*x3 + B*x2 + C*x1
	y = t3*y4 + A*y3 + B*y2 + C*y1
}

// <https://stackoverflow.com/a/41401223/7517185>
// x = a * (1-t)³ + b * 3 * (1-t)²t + c * 3 * (1-t)t² + d * t³
//------------------------------------------------------------
// x = a - 3at + 3at² - at³ 
//       + 3bt - 6bt² + 3bt³
//             + 3ct² - 3ct³
//                    + dt³
//--------------------------------
// x = - at³  + 3bt³ - 3ct³ + dt³
//     + 3at² - 6bt² + 3ct²
//     - 3at + 3bt
//     + a
//--------------------------------
// 0 = t³ (-a+3b-3c+d) +  => A
//     t² (3a-6b+3c)   +  => B
//     t  (-3a+3b)     +  => c
//     a - x              => D
//--------------------------------

var A = d - 3*c + 3*b - a,
    B = 3*c - 6*b + 3*a,
    C = 3*b - 3*a,
    D = a-x;

// So we need to solve At³ + Bt² + Ct + D = 0 

void __cdecl Routing_Maths_Vector2D_FUN_00406520(Point2F *r,Point2F *a,Point2F *b,Point2F *c,Point2F *d,float scalar)
{
	float fVar1;
	float fVar2;
	float fVar3;
	float fVar4;
	float fVar5;
	float fVar6;
	
	
	float fVar1 = (b->x * 3.0) + a->x;
	float scalarSqr = scalar * scalar;
	fVar4 = (fVar1 - a->x) * 3.0;
	xVar2 = ((c->x - (d->x * 3.0)) - fVar1) * 3.0 - fVar4;
	fVar1 = d->y;
	fVar6 = a->y + (b->y * 3.0);
	fVar2 = c->y;

	
	//float scalar1 = scalar;
	float scalarSqr = scalar * scalar;          // sqr(scalar)
	float scalarCbe = scalar * scalar * scalar; // cbe(scalar)

	float xVar0 = a->x + (b->x*3.0);
	float yVar0 = a->y + (b->y*3.0);

	float xVar1 = (xVar0-a->x) * 3.0;
	float yVar1 = (yVar0-a->y) * 3.0;

	float xVar2 = ((c->x-(d->x*3.0)) - xVar0) * 3.0 - xVar1;
	float yVar2 = ((c->y-(d->y*3.0)) - yVar0) * 3.0 - yVar1;

	// result
	r->x = a->x + ((xVar1)*scalar) + ((xVar2)*scalarSqr) + (((c->x-a->x) - xVar1 - xVar2)*scalarCbe);
	r->y = a->y + ((yVar1)*scalar) + ((yVar2)*scalarSqr) + (((c->y-a->y) - yVar1 - yVar2)*scalarCbe);


	float xVar1 = ((a->x+(b->x*3.0)) - a->x) * 3.0;
	// (simplified)
	float xVar1 = (b->x * 3.0) * 3.0; // * 9.0

	float xVar2 = (((c->x-(d->x*3.0)) - (a->x+(b->x*3.0))) * 3.0) - (b->x * 3.0 * 3.0);
	//float xVar2 = ((c->x - (d->x * 3.0)) - (b->x * 3.0) + a->x) * 3.0 - xVar1;
	
	//float yVar1 = (((c->x-(d->x*3.0)) - (a->x+(b->x*3.0))) * 3.0) - (b->x * 3.0 * 3.0);

	float yVar01 = ((a->y+(b->y*3.0)) - a->y) * 3.0;
	float yVar1 = ((a->y + (b->y * 3.0)) - a->y) * 3.0;
	// simplified
	float yVar1 = (b->y * 3.0 * 3.0);


	out_point->x = a->x + ((xVar1)*scalar) + ((xVar2)*scalarSqr) + (((c->x-a->x) - xVar1 - xVar2)*scalarCbe);
	
	out_point->y = a->y + ((yVar1)*scalar) + ((yVar2)*scalarSqr) + (((c->y-a->y) - yVar1 - yVar2)*scalarCbe);

	// out_point->x = (xVar1 * scalar) + (xVar2 * scalarSqr) + ((((c->x - a->x) - xVar1) - xVar2) * scalarCbe) + a->x;



	// out_point->y = a->y + (yVar1*scalar) + (yVar2*scalarSqr) + ((((c->y-a->y) - yVar1) - yVar2)*scalarCbe);
	
	// out_point->y = (yVar2 * scalarSqr) + (fVar3 * scalar) + ((((c->y - a->y) - fVar3) - fVar1) * scalarCbe) + a->y;
	


	//
	out_point->x = fVar4 * scalar +
								 fVar3 * scalarSqr + (((c->x - a->x) - fVar4) - fVar3) * scalarSqr * scalar +
								 a->x;

	float fVar3 = ((a->y + (b->y * 3.0)) - a->y) * 3.0;
	// simplified
	float fVar3 = (b->y * 3.0) * 3.0;
	float fVar1 = ((c->y - d->y * 3.0) - fVar6) * 3.0 - fVar3;
	out_point->y = fVar1 * scalarSqr +
								 fVar3 * scalar + (((c->y - a->y) - fVar3) - fVar1) * scalarSqr * scalar +
								 a->y;
	return;
}

// <https://stackoverflow.com/a/41401223/7517185>
// x = a * (1-t)³ + b * 3 * (1-t)²t + c * 3 * (1-t)t² + d * t³
//------------------------------------------------------------
// x = a - 3at + 3at² - at³ 
//       + 3bt - 6bt² + 3bt³
//             + 3ct² - 3ct³
//                    + dt³
//--------------------------------
// x = - at³  + 3bt³ - 3ct³ + dt³
//     + 3at² - 6bt² + 3ct²
//     - 3at + 3bt
//     + a
//--------------------------------
// 0 = t³ (-a+3b-3c+d) +  => A
//     t² (3a-6b+3c)   +  => B
//     t  (-3a+3b)     +  => c
//     a - x              => D
//--------------------------------

var A = d - 3*c + 3*b - a,
    B = 3*c - 6*b + 3*a,
    C = 3*b - 3*a,
    D = a-x;

// So we need to solve At³ + Bt² + Ct + D = 0 





// sqrt(((a.x-b.x)*(a.x-b.x)) + ((a.y-b.y)*(a.y-b.y)))

float10 Routing_Vector2DDistance(Point2F *a,Point2F *b)
{
	return Maths_Vector2DDistance(a, b);
	//return std::sqrt(((a->x-b->x)*(a->x-b->x))+((a->y-b->y)*(a->y-b->y)));
}



// ref_r = norm(ref_r) * l
// NOTE: Unlike `Maths_Vector2DSetLength`, this function modifies the input point.

void Routing_Vector2DChangeLength(Point2F *ref_r,float l)
{
	Maths_Vector2DSetLength(ref_r, ref_r, l);

	//float m = std::sqrt((ref_r->x*ref_r->x)+(ref_r->y*ref_r->y));
	//ref_r->x *= (1.0f/m) * l;
	//ref_r->y *= (1.0f/m) * l;
}

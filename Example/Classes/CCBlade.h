/*
 * cocos2d+ext for iPhone
 *
 * Copyright (c) 2011 - Ngo Duc Hiep
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#import <Foundation/Foundation.h>
#import "cocos2d.h"

#define USE_LAGRANGE        1
#define USE_STL_LIST        1
#define USE_UPDATE_FOR_POP  1

//static inline GLPoint ccpMult(const GLPoint v, const CGFloat s) { return ccp(v.x*s, v.y*s); }


typedef struct { GLfloat x; GLfloat y; } GLPoint;

static CGPoint GLPointToCGPoint(GLPoint point) { return CGPointMake(point.x, point.y); }

static GLPoint GLPointMake(CGFloat x, CGFloat y) { GLPoint p; p.x = x; p.y = y; return p; }

static GLPoint CGPointToGLPoint(CGPoint point) { GLPoint p; p.x = point.x; p.y = point.y; return p; }

static inline GLPoint ccpGL( GLfloat x, GLfloat y )
{
    return GLPointMake(x, y);
}

static inline GLPoint ccpSubGL(const GLPoint v1, const GLPoint v2){   return ccpGL(v1.x - v2.x, v1.y - v2.y);}

static GLPoint ccpRotateByAngleGL(GLPoint v, GLPoint pivot, GLfloat angle);


GLPoint ccpRotateByAngleGL(GLPoint v, GLPoint pivot, GLfloat angle)
{
    GLPoint r = ccpSubGL(v, pivot);
    GLfloat cosa = cosf(angle), sina = sinf(angle);
    GLfloat t = r.x;
    r.x = t*cosa - r.y*sina + pivot.x;
    r.y = t*sina + r.y*cosa + pivot.y;
    return r;
}

  //GLfloat ccpDistanceGL(const GLPoint v1, const GLPoint v2);





inline float fangle(GLPoint vect);
inline float lagrange1(GLPoint p1, GLPoint p2, GLfloat x);

inline void CGPointSet(GLPoint *v, GLfloat x, GLfloat y);
inline void f1(GLPoint p1, GLPoint p2, GLfloat d, GLPoint *o1, GLPoint *o2);

@interface CCBlade : CCNode {
	int count;
	GLPoint *vertices;
	GLPoint *coordinates;
	BOOL reset;
    BOOL _finish;
    BOOL _willPop;
    
    float timeSinceLastPop;
    float popTimeInterval;
}
@property (readonly) unsigned int pointLimit;
@property(strong) CCTexture2D *texture;
@property(nonatomic) GLfloat width;
@property (nonatomic) BOOL autoDim;
@property(nonatomic,strong)NSMutableArray *path;

+ (id) bladeWithMaximumPoint:(int) limit;
- (id) initWithMaximumPoint:(int) limit;
- (void) push:(GLPoint) v;
- (void) pop:(int) n;
- (void) clear;
- (void) reset;
- (void) dim:(BOOL) dim;
- (void) finish;
@end

#import "EJCanvasContext2D.h"

@interface EJCanvasContext2DTexture : EJCanvasContext2D {
	BOOL msaaNeedsResolving;
	EJTexture * texture;
}

@property (readonly, nonatomic) EJTexture * texture;

@end

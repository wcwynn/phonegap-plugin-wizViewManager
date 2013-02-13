/* WizWebView - Creates Instance of wizard UIWebView.
 *
 * @author WizCorp Inc. [ Incorporated Wizards ] 
 * @copyright 2011
 * @file WizWebView.h for PhoneGap
 *
 */ 

#import <Foundation/Foundation.h>
#ifdef CORDOVA_FRAMEWORK
#import <Cordova/CDVPlugin.h>
#import <Cordova/CDVCordovaView.h>
#else
#import "CDVPlugin.h"
#import "CDVCordovaView.h"
#endif


#import <QuartzCore/QuartzCore.h>
#import "JavaScriptCore/JavaScriptCore.h"
#import "EJConvert.h"
#import "EJCanvasContext.h"
#import "EJPresentable.h"
#import "EJGLProgram2D.h"
#import "EJGLProgram2DRadialGradient.h"
#import "EJOpenALManager.h"

#define EJECTA_VERSION @"1.2"
#define EJECTA_APP_FOLDER @"www/"

#define EJECTA_BOOT_JS @"phonegap/plugin/wizViewManager/ejecta.js"
#define WIZVIEWMANAGER_BOOT_JS @"phonegap/plugin/wizViewManager/wizViewCanvasManager.js"
#define EJECTA_MAIN_JS @"index.js"

@protocol EJTouchDelegate
- (void)triggerEvent:(NSString *)name all:(NSSet *)all changed:(NSSet *)changed remaining:(NSSet *)remaining;
@end

@protocol EJLifecycleDelegate
- (void)resume;
- (void)pause;
@end

@class EJTimerCollection;

@interface WizCanvasView : UIViewController {
    BOOL paused;
	BOOL landscapeMode;
	JSGlobalContextRef jsGlobalContext;
	UIView * window;
	UIImageView * loadingScreen;
	NSObject<EJTouchDelegate> * touchDelegate;
	NSObject<EJLifecycleDelegate> * lifecycleDelegate;
	
	EJTimerCollection * timers;
	NSTimeInterval currentTime;
	
	EAGLContext * glCurrentContext;
	EAGLContext * glContext2D;
	EAGLSharegroup * glSharegroup;
	CADisplayLink * displayLink;
	
	NSMutableDictionary * textureCache;
	EJOpenALManager * openALManager;
	EJGLProgram2D * glProgram2DFlat;
	EJGLProgram2D * glProgram2DTexture;
	EJGLProgram2D * glProgram2DAlphaTexture;
	EJGLProgram2D * glProgram2DPattern;
	EJGLProgram2DRadialGradient * glProgram2DRadialGradient;
	
	NSOperationQueue * opQueue;
	EJCanvasContext * currentRenderingContext;
	EJCanvasContext<EJPresentable> * screenRenderingContext;
	
	float internalScaling;
}

- (id)initWithWindow:(UIView *)window name:(NSString*)viewName sourceToLoad:(NSString*)src;

- (void)run:(CADisplayLink *)sender;
- (void)pause;
- (void)resume;
- (void)clearCaches;
- (NSString *)pathForResource:(NSString *)resourcePath;
- (JSValueRef)createTimer:(JSContextRef)ctx argc:(size_t)argc argv:(const JSValueRef [])argv repeat:(BOOL)repeat;
- (JSValueRef)deleteTimer:(JSContextRef)ctx argc:(size_t)argc argv:(const JSValueRef [])argv;

- (void)hideLoadingScreen;
// Added for pure script injection wizardry - ao.
- (void)evaluateScript:(NSString *)path;
- (void)loadScriptAtPath:(NSString *)path;
- (JSValueRef)loadModuleWithId:(NSString *)moduleId module:(JSValueRef)module exports:(JSValueRef)exports;
- (JSValueRef)invokeCallback:(JSObjectRef)callback thisObject:(JSObjectRef)thisObject argc:(size_t)argc argv:(const JSValueRef [])argv;
- (void)logException:(JSValueRef)exception ctx:(JSContextRef)ctxp;


+ (WizCanvasView *)instance;

// Todo: clean this up somehow?
@property (nonatomic, readonly) NSMutableDictionary * textureCache;
@property (nonatomic, readonly) EJOpenALManager * openALManager;
@property (nonatomic, readonly) EJGLProgram2D * glProgram2DFlat;
@property (nonatomic, readonly) EJGLProgram2D * glProgram2DTexture;
@property (nonatomic, readonly) EJGLProgram2D * glProgram2DAlphaTexture;
@property (nonatomic, readonly) EJGLProgram2D * glProgram2DPattern;
@property (nonatomic, readonly) EJGLProgram2DRadialGradient * glProgram2DRadialGradient;

@property (nonatomic, readonly) BOOL landscapeMode;
@property (nonatomic, readonly) JSGlobalContextRef jsGlobalContext;
@property (nonatomic, readonly) EAGLContext * glContext2D;
@property (nonatomic, readonly) EAGLSharegroup * glSharegroup;
@property (nonatomic, readonly) UIView * window;
@property (nonatomic, retain) NSObject<EJTouchDelegate> * touchDelegate;
@property (nonatomic, retain) NSObject<EJLifecycleDelegate> * lifecycleDelegate;

@property (nonatomic, readonly) NSOperationQueue * opQueue;
@property (nonatomic, assign) EJCanvasContext * currentRenderingContext;
@property (nonatomic, assign) EJCanvasContext<EJPresentable> * screenRenderingContext;
@property (nonatomic) float internalScaling;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

@end

//
//  TextViewController.h
//  Untitled
//
//  Created by David Petrie on 27/01/11.
//  Copyright 2011 n/a. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface TextViewController : UIViewController <UITextViewDelegate>
{
    IBOutlet UITextView * codeTextView;
    IBOutlet UITextView * outTextView;
}


- (IBAction)editingDone:(id)sender;

@end

//
//  TextViewController.m
//  Untitled
//
//  Created by David Petrie on 27/01/11.
//  Copyright 2011 n/a. All rights reserved.
//

#import "TextViewController.h"
#include "js.h"

@implementation TextViewController

- (id) init
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
    {
        return self = [super initWithNibName:@"TextViewController.iPad" bundle:[NSBundle mainBundle]];
    }
    else
    {
        return self = [super initWithNibName:@"TextViewController" bundle:[NSBundle mainBundle]];
    }
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


- (void)viewDidUnload
{
    [super viewDidUnload];
}


- (void)dealloc
{
    [super dealloc];
}


- (IBAction)editingDone:(id)sender
{
    [codeTextView resignFirstResponder];
    
    NSString * str = codeTextView.text;
    
    char res[256];
    bzero(res, 256);
    
    RunJS([str UTF8String], res, 255);
    
    printf("%s\n", res);
    
    [outTextView setText:[NSString stringWithUTF8String:res]];
}


- (BOOL)textViewShouldEndEditing:(UITextView *)textView
{
    return YES;
}


- (void)textViewDidEndEditing:(UITextView *)textView
{
}

@end

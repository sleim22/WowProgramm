/**
 * @file
 * @brief The main file with the main entry point
 *
 * @author Lukas Deutscher
 * @date 26.07.2018
 */

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <iostream>

/**
 * @brief The default main function
 *
 * @param argc The number of command line arguments
 * @param argv The command line arguments as an array of c-style strings
 * @return int The Program exit code
 */
//int main(int argc, char** argv)
//{
//	std::cout << "Hello World" << std::endl;
//
//    return 0;
//}

class WoWApp : public wxApp
{
public: 
	virtual bool OnInit();
};
class Frame : public wxFrame
{
public:
	Frame();
};

enum
{
	ID_Hello = 1
};

wxIMPLEMENT_APP(WoWApp);

bool WoWApp::OnInit()
{
	Frame *frame = new Frame();
	frame->Show(true);
	return true;
}

Frame::Frame()
	: wxFrame(NULL, wxID_ANY, "Frame")
{

}
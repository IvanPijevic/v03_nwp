#include <windows.h>
#include <stdexcept>

#include "nwpdlg.h"
#include "resource.h"


class main_dialog : public vsite::nwp::dialog 
{
public:
	POINT point;

protected:
	int idd() const override
	{ 
		return IDD_DIALOG1; 
	}

	bool on_init_dialog() override
	{
		set_int(IDC_EDIT1, point.x);
		set_int(IDC_EDIT1, point.y);

		return true;
	}

	bool on_ok() override
	{
		//get current values from edit controls
		try
		{
			point.x = get_int(IDC_EDIT1);
			point.y = get_int(IDC_EDIT1);
		}
		catch(std::runtime_error& err)
		{
			MessageBox(*this, err.what(), "Error!", MB_OK | MB_ICONERROR);
			return false;
		}

		return true;
	}

	void on_cancel() override { }
	bool on_command(int id, int code) override { return false; }
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	main_dialog dlg;
	
	GetCursorPos(&dlg.point);

	if(dlg.do_modal(instance, 0) == IDOK)
	{
		SetCursorPos(dlg.point.x, dlg.point.y);
	}

	return 0;
}

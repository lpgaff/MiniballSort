// Very basic ROOT GUI to perform sorting of Miniball data
//
// Liam Gaffney (liam.gaffney@liverpool.ac.uk) - 21/01/2022

#include "MiniballGUI.hh"

ClassImp(MiniballGUI)
ClassImp(MyDialog)

MiniballGUI::MiniballGUI() {

	//-------------------//
	// Create main frame //
	//-------------------//
	main_frame = new TGMainFrame( gClient->GetRoot(), 1000, 300, kMainFrame | kHorizontalFrame );

	// terminate ROOT session when window is closed
	main_frame->Connect( "CloseWindow()", "TApplication", gApplication, "Terminate()" );
	main_frame->DontCallClose();


	//----------------------------------//
	// Create sub frames and separators //
	//----------------------------------//

	// Left frame - for file list
	left_frame = new TGVerticalFrame( main_frame, 150, 300 );
	left_frame->SetName( "left_frame" );
	main_frame->AddFrame( left_frame, new TGLayoutHints( kLHintsLeft ) );
	
	// File button box
	fbut_frame = new TGHorizontalFrame( left_frame, 150, 20 );
	fbut_frame->SetName( "fbut_frame" );
	left_frame->AddFrame( fbut_frame, new TGLayoutHints( kLHintsBottom | kLHintsExpandX ) );

	// Vertical separator
	fVertical_0 = new TGVertical3DLine( main_frame, 8, 300 );
	fVertical_0->SetName( "fVertical_0" );
	main_frame->AddFrame( fVertical_0, new TGLayoutHints( kLHintsLeft | kLHintsTop, 2, 2, 2, 2 ) );
	
	// Centre frame - Files, directories, buttons, etc
	centre_frame = new TGVerticalFrame( main_frame, 600, 300 );
	centre_frame->SetName( "centre_frame" );
	main_frame->AddFrame( centre_frame, new TGLayoutHints( kLHintsCenterX ) );

	centre_files = new TGHorizontalFrame( centre_frame, 600, 300 );
	centre_files->SetName( "centre_files" );
	centre_frame->AddFrame( centre_files, new TGLayoutHints( kLHintsCenterX ) );

	centre_progress = new TGVerticalFrame( centre_frame, 600, 300 );
	centre_progress->SetName( "centre_progress" );
	centre_frame->AddFrame( centre_progress, new TGLayoutHints( kLHintsCenterX ) );

	fHorizontal_0 = new TGHorizontal3DLine( centre_frame, 600, 8 );
	fHorizontal_0->SetName( "fHorizontal_0" );
	centre_frame->AddFrame( fHorizontal_0, new TGLayoutHints( kLHintsLeft | kLHintsTop, 2, 2, 2, 2 ) );

	centre_progress = new TGVerticalFrame( centre_frame, 600, 300 );
	centre_progress->SetName( "centre_progress" );
	centre_frame->AddFrame( centre_progress, new TGLayoutHints( kLHintsCenterX ) );

	centre_go = new TGHorizontalFrame( centre_frame, 600, 300 );
	centre_go->SetName( "centre_go" );
	centre_frame->AddFrame( centre_go, new TGLayoutHints( kLHintsCenterX ) );

	centre_label = new TGVerticalFrame( centre_files, 180, 300 );
	centre_label->SetName( "centre_label" );
	centre_files->AddFrame( centre_label, new TGLayoutHints( kLHintsCenterX ) );

	centre_text = new TGVerticalFrame( centre_files, 500, 300 );
	centre_text->SetName( "centre_text" );
	centre_files->AddFrame( centre_text, new TGLayoutHints( kLHintsCenterX ) );

	centre_button = new TGVerticalFrame( centre_files, 10, 300 );
	centre_button->SetName( "centre_button" );
	centre_files->AddFrame( centre_button, new TGLayoutHints( kLHintsCenterX ) );


	//-------------------------//
	// Open/Save config button //
	//-------------------------//

	// Setup file open
	but_open = new TGTextButton( left_frame, "Open setup", -1, TGTextButton::GetDefaultGC()(),
								 TGTextButton::GetDefaultFontStruct(), kRaisedFrame );
	but_open->SetTextJustify( 36 );
	but_open->SetMargins( 0, 0, 0, 0 );
	but_open->SetWrapLength( -1 );
	but_open->Resize( 25, 30 );
	left_frame->AddFrame( but_open, new TGLayoutHints( kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2 ) );
	
	// Setup file save
	but_save = new TGTextButton( left_frame, "Save setup", -1, TGTextButton::GetDefaultGC()(),
									TGTextButton::GetDefaultFontStruct(), kRaisedFrame );
	but_save->SetTextJustify( 36 );
	but_save->SetMargins( 0, 0, 0, 0 );
	but_save->SetWrapLength( -1 );
	but_save->Resize( 25, 30 );
	left_frame->AddFrame( but_save, new TGLayoutHints( kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2 ) );
	

	//---------------//
	// Create labels //
	//---------------//
	
	// Run files
	lab_run_files = new TGLabel( left_frame, "List of file names" );
	lab_run_files->SetTextJustify( 36 );
	lab_run_files->SetMargins( 0, 0, 0, 0 );
	lab_run_files->SetWrapLength( -1 );
	lab_run_files->Resize( 80, lab_run_files->GetDefaultHeight() );
	main_frame->AddFrame( lab_run_files,
						 new TGLayoutHints( kLHintsCenterX | kLHintsTop, 2, 2, 2, 2 ) );
	
	// Settings file
	lab_set_file = new TGLabel( centre_label, "Settings file" );
	lab_set_file->SetTextJustify( 36 );
	lab_set_file->SetMargins( 0, 0, 0, 0 );
	lab_set_file->SetWrapLength( -1 );
	lab_set_file->Resize( 80, lab_set_file->GetDefaultHeight() );
	centre_label->AddFrame( lab_set_file,
						 new TGLayoutHints( kLHintsCenterX | kLHintsTop, 2, 2, 5, 5 ) );

	// Calibration file
	lab_cal_file = new TGLabel( centre_label, "Calibration file" );
	lab_cal_file->SetTextJustify( 36 );
	lab_cal_file->SetMargins( 0, 0, 0, 0 );
	lab_cal_file->SetWrapLength( -1 );
	lab_cal_file->Resize( 80, lab_cal_file->GetDefaultHeight() );
	centre_label->AddFrame( lab_cal_file,
						 new TGLayoutHints( kLHintsCenterX | kLHintsTop, 2, 2, 5, 5 ) );
	
	// Reaction file
	lab_rea_file = new TGLabel( centre_label, "Reaction file" );
	lab_rea_file->SetTextJustify( 36 );
	lab_rea_file->SetMargins( 0, 0, 0, 0 );
	lab_rea_file->SetWrapLength( -1 );
	lab_rea_file->Resize( 80, lab_rea_file->GetDefaultHeight() );
	centre_label->AddFrame( lab_rea_file,
						 new TGLayoutHints( kLHintsCenterX | kLHintsTop, 2, 2, 5, 5 ) );

	// Output directory
	lab_out_dir = new TGLabel( centre_label, "Output directory" );
	lab_out_dir->SetTextJustify( 36 );
	lab_out_dir->SetMargins( 0, 0, 0, 0 );
	lab_out_dir->SetWrapLength( -1 );
	lab_out_dir->Resize( 80, lab_out_dir->GetDefaultHeight() );
	centre_label->AddFrame( lab_out_dir,
						 new TGLayoutHints( kLHintsCenterX | kLHintsTop, 2, 2, 5, 5 ) );

	// Output file
	lab_out_file = new TGLabel( centre_label, "Histogram file" );
	lab_out_file->SetTextJustify( 36 );
	lab_out_file->SetMargins( 0, 0, 0, 0 );
	lab_out_file->SetWrapLength( -1 );
	lab_out_file->Resize( 80, lab_out_file->GetDefaultHeight() );
	centre_label->AddFrame( lab_out_file,
						 new TGLayoutHints( kLHintsCenterX | kLHintsTop, 2, 2, 5, 5 ) );


	//-----------------//
	// Create list box //
	//-----------------//
	
	// Run files
	run_list_box = new TGListBox( left_frame, -1, kSunkenFrame );
	run_list_box->SetName( "run_list_box" );
	run_list_box->Resize( 300, 256 );
	left_frame->AddFrame( run_list_box, new TGLayoutHints( kLHintsLeft | kLHintsTop | kLHintsExpandY, 2, 2, 2, 2 ) );
	
	run_selected = new TList;
	run_list_box->SetMultipleSelections( true );

	//---------------------//
	// Create text entries //
	//---------------------//

	// Add file
	text_add_file = new TGTextEntry( left_frame );
	text_add_file->SetMaxLength( 4096 );
	text_add_file->SetAlignment( kTextLeft );
	text_add_file->Resize( 300, text_add_file->GetDefaultHeight() );
	left_frame->AddFrame( text_add_file, new TGLayoutHints( kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2 ) );
	
	// Settings file
	text_set_file = new TGTextEntry( centre_text );
	text_set_file->SetMaxLength( 4096 );
	text_set_file->SetAlignment( kTextLeft );
	text_set_file->Resize( 400, text_set_file->GetDefaultHeight() );
	centre_text->AddFrame( text_set_file, new TGLayoutHints( kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2 ) );

	// Calibration file
	text_cal_file = new TGTextEntry( centre_text );
	text_cal_file->SetMaxLength( 4096 );
	text_cal_file->SetAlignment( kTextLeft );
	text_cal_file->Resize( 400, text_cal_file->GetDefaultHeight() );
	centre_text->AddFrame( text_cal_file, new TGLayoutHints( kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2 ) );

	// Reaction file
	text_rea_file = new TGTextEntry( centre_text );
	text_rea_file->SetMaxLength( 4096 );
	text_rea_file->SetAlignment( kTextLeft );
	text_rea_file->Resize( 400, text_rea_file->GetDefaultHeight() );
	centre_text->AddFrame( text_rea_file, new TGLayoutHints( kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2 ) );
	
	// Output directory
	text_out_dir = new TGTextEntry( centre_text, "./sorted" );
	text_out_dir->SetMaxLength( 4096 );
	text_out_dir->SetAlignment( kTextLeft );
	text_out_dir->Resize( 400, text_out_dir->GetDefaultHeight() );
	centre_text->AddFrame( text_out_dir, new TGLayoutHints( kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2 ) );
	
	// Output file
	text_out_file = new TGTextEntry( centre_text );
	text_out_file->SetMaxLength( 4096 );
	text_out_file->SetAlignment( kTextLeft );
	text_out_file->Resize( 400, text_out_file->GetDefaultHeight() );
	centre_text->AddFrame( text_out_file, new TGLayoutHints( kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2 ) );
	
	//----------------------//
	// Create check buttons //
	//----------------------//

	check_mbs = new TGCheckButton( centre_go, "MBS data" );
	centre_go->AddFrame( check_mbs, new TGLayoutHints( kLHintsLeft, 2, 2, 2, 2 ) );

	check_source = new TGCheckButton( centre_go, "Source data" );
	centre_go->AddFrame( check_source, new TGLayoutHints( kLHintsLeft, 2, 2, 2, 2 ) );

	check_force = new TGCheckButton( centre_go, "Force convert" );
	centre_go->AddFrame( check_force, new TGLayoutHints( kLHintsLeft, 2, 2, 2, 2 ) );

	check_event = new TGCheckButton( centre_go, "Rebuild events" );
	centre_go->AddFrame( check_event, new TGLayoutHints( kLHintsLeft, 2, 2, 2, 2 ) );

	check_ebis = new TGCheckButton( centre_go, "EBIS only" );
	centre_go->AddFrame( check_ebis, new TGLayoutHints( kLHintsLeft, 2, 2, 2, 2 ) );


	//-----------------------//
	// Create action buttons //
	//-----------------------//

	// Select files
	but_sel = new TGTextButton( fbut_frame, "Select", -1, TGTextButton::GetDefaultGC()(),
							   TGTextButton::GetDefaultFontStruct(), kRaisedFrame );
	but_sel->SetTextJustify( 36 );
	but_sel->SetMargins( 0, 0, 0, 0 );
	but_sel->SetWrapLength( -1 );
	but_sel->Resize( 65, 46 );
	fbut_frame->AddFrame( but_sel, new TGLayoutHints( kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2 ) );
	
	// Add files
	but_add = new TGTextButton( fbut_frame, "Add", -1, TGTextButton::GetDefaultGC()(),
							   TGTextButton::GetDefaultFontStruct(), kRaisedFrame );
	but_add->SetTextJustify( 36 );
	but_add->SetMargins( 0, 0, 0, 0 );
	but_add->SetWrapLength( -1 );
	but_add->Resize( 65, 46 );
	fbut_frame->AddFrame( but_add, new TGLayoutHints( kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2 ) );
	
	// Remove files
	but_del = new TGTextButton( fbut_frame, "Remove", -1, TGTextButton::GetDefaultGC()(),
							   TGTextButton::GetDefaultFontStruct(), kRaisedFrame );
	but_del->SetTextJustify( 36 );
	but_del->SetMargins( 0, 0, 0, 0 );
	but_del->SetWrapLength( -1 );
	but_del->Resize( 65, 46 );
	fbut_frame->AddFrame( but_del, new TGLayoutHints( kLHintsRight | kLHintsExpandX, 2, 2, 2, 2 ) );

	// Settings file
	but_set = new TGTextButton( centre_button, "Open", -1, TGTextButton::GetDefaultGC()(),
							   TGTextButton::GetDefaultFontStruct(), kRaisedFrame );
	but_set->SetTextJustify( 36 );
	but_set->SetMargins( 0, 0, 0, 0 );
	but_set->SetWrapLength( -1 );
	but_set->Resize( 65, 46 );
	centre_button->AddFrame( but_set, new TGLayoutHints( kLHintsRight | kLHintsExpandX, 2, 2, 7, 2 ) );

	// Calibration file
	but_cal = new TGTextButton( centre_button, "Open", -1, TGTextButton::GetDefaultGC()(),
							   TGTextButton::GetDefaultFontStruct(), kRaisedFrame );
	but_cal->SetTextJustify( 36 );
	but_cal->SetMargins( 0, 0, 0, 0 );
	but_cal->SetWrapLength( -1 );
	but_cal->Resize( 65, 46 );
	centre_button->AddFrame( but_cal, new TGLayoutHints( kLHintsRight | kLHintsExpandX, 2, 2, 2, 2 ) );

	// Reaction file
	but_rea = new TGTextButton( centre_button, "Open", -1, TGTextButton::GetDefaultGC()(),
							   TGTextButton::GetDefaultFontStruct(), kRaisedFrame );
	but_rea->SetTextJustify( 36 );
	but_rea->SetMargins( 0, 0, 0, 0 );
	but_rea->SetWrapLength( -1 );
	but_rea->Resize( 65, 46 );
	centre_button->AddFrame( but_rea, new TGLayoutHints( kLHintsRight | kLHintsExpandX, 2, 2, 2, 2 ) );

	// Output directory
	but_dir = new TGTextButton( centre_button, "Select", -1, TGTextButton::GetDefaultGC()(),
							   TGTextButton::GetDefaultFontStruct(), kRaisedFrame );
	but_dir->SetTextJustify( 36 );
	but_dir->SetMargins( 0, 0, 0, 0 );
	but_dir->SetWrapLength( -1 );
	but_dir->Resize( 65, 46 );
	centre_button->AddFrame( but_dir, new TGLayoutHints( kLHintsRight | kLHintsExpandX, 2, 2, 2, 2 ) );

	// Output file
	but_out = new TGTextButton( centre_button, "Open", -1, TGTextButton::GetDefaultGC()(),
							   TGTextButton::GetDefaultFontStruct(), kRaisedFrame );
	but_out->SetTextJustify( 36 );
	but_out->SetMargins( 0, 0, 0, 0 );
	but_out->SetWrapLength( -1 );
	but_out->Resize( 65, 46 );
	centre_button->AddFrame( but_out, new TGLayoutHints( kLHintsRight | kLHintsExpandX, 2, 2, 2, 2 ) );

	// Go sorting
	but_sort = new TGTextButton( centre_go, "GO!", -1, TGTextButton::GetDefaultGC()(),
							   TGTextButton::GetDefaultFontStruct(), kDoubleBorder );
	but_sort->SetTextJustify( 36 );
	but_sort->SetMargins( 0, 0, 0, 0 );
	but_sort->SetWrapLength( -1 );
	but_sort->Resize( 65, 46 );
	but_sort->SetTextColor( TColor::Number2Pixel( kWhite ) );
	but_sort->SetBackgroundColor( TColor::Number2Pixel( kGreen+1 ) );
	centre_go->AddFrame( but_sort, new TGLayoutHints( kLHintsRight | kLHintsExpandX ) );

	
	//---------------//
	// Progress bars //
	//---------------//
	prog_conv.reset( new TGHProgressBar( centre_progress, TGProgressBar::kFancy, 400 ) );
	prog_sort.reset( new TGHProgressBar( centre_progress, TGProgressBar::kFancy, 400 ) );
	prog_evnt.reset( new TGHProgressBar( centre_progress, TGProgressBar::kFancy, 400 ) );
	prog_hist.reset( new TGHProgressBar( centre_progress, TGProgressBar::kFancy, 400 ) );
	prog_conv->ShowPosition( true, false, "Converter" );
	prog_sort->ShowPosition( true, false, "TimeSorter" );
	prog_evnt->ShowPosition( true, false, "EventBuilder" );
	prog_hist->ShowPosition( true, false, "Histogrammer" );
	centre_progress->AddFrame( prog_conv.get(), new TGLayoutHints(kLHintsTop|kLHintsLeft|
															kLHintsExpandX,5,5,5,10) );
	centre_progress->AddFrame( prog_sort.get(), new TGLayoutHints(kLHintsTop|kLHintsLeft|
															kLHintsExpandX,5,5,5,10) );
	centre_progress->AddFrame( prog_evnt.get(), new TGLayoutHints(kLHintsTop|kLHintsLeft|
															kLHintsExpandX,5,5,5,10) );
	centre_progress->AddFrame( prog_hist.get(), new TGLayoutHints(kLHintsTop|kLHintsLeft|
															kLHintsExpandX,5,5,5,10) );


	//-----------------//
	// Open the window //
	//-----------------//

	// Set a name to the main frame
	main_frame->SetWindowName( "mb_sort" );
	
	// Map all sub windows
	main_frame->MapSubwindows();
	
	// Initialize the layout algorithm via Resize()
	main_frame->Resize( main_frame->GetDefaultSize() );
	
	// Map windows
	main_frame->MapWindow();
	//main_frame->Print();
	
	
	//----------//
	// Defaults //
	//----------//
	text_add_file->SetText( "R1_0" );

	
	//----------------//
	// Button presses //
	//----------------//
	but_save->Connect( "Clicked()", "MiniballGUI", this, "on_save_clicked()" );
	but_open->Connect( "Clicked()", "MiniballGUI", this, "on_open_clicked()" );
	but_sel->Connect( "Clicked()", "MiniballGUI", this, "on_sel_clicked()" );
	but_add->Connect( "Clicked()", "MiniballGUI", this, "on_add_clicked()" );
	text_add_file->Connect( "ReturnPressed()", "MiniballGUI", this, "on_add_clicked()" );
	but_del->Connect( "Clicked()", "MiniballGUI", this, "on_del_clicked()" );
	but_sort->Connect( "Clicked()", "MiniballGUI", this, "on_sort_clicked()" );
	but_set->Connect( "Clicked()", "MiniballGUI", this, "on_set_clicked()" );
	but_cal->Connect( "Clicked()", "MiniballGUI", this, "on_cal_clicked()" );
	but_rea->Connect( "Clicked()", "MiniballGUI", this, "on_rea_clicked()" );
	but_dir->Connect( "Clicked()", "MiniballGUI", this, "on_dir_clicked()" );
	but_out->Connect( "Clicked()", "MiniballGUI", this, "on_out_clicked()" );

	
	//clean up
	filelist.clear();
	filestatus.clear();
	
}

MiniballGUI::~MiniballGUI() {
	
	// Clean up main frame...
	main_frame->Cleanup();
	delete main_frame;

}

TString MiniballGUI::get_filename() {
	
	// Configure file dialog
	TGFileInfo fi;
	fi.SetMultipleSelection( false );
	TString dir(".");
	fi.fIniDir = StrDup(dir);
	
	// Open a file dialog
	auto open_mode = kFDOpen;
	new TGFileDialog( gClient->GetRoot(), main_frame, open_mode, &fi );
	
	return fi.fFilename;
	
}

TString MiniballGUI::get_directory() {
	
	// Configure file dialog
	TGFileInfo fi;
	fi.SetMultipleSelection( false );
	TString dir(".");
	fi.fIniDir = StrDup(dir);
	
	// Open a file dialog
	auto open_mode = kDOpen;
#if ( ROOTVER == 5 || ( ROOTVER == 6 && ROOTSUBVER < 24 ) )
	open_mode = kFDOpen;
#endif
	new TGFileDialog( gClient->GetRoot(), main_frame, open_mode, &fi );
	
	return fi.fIniDir;
	
}

void MiniballGUI::on_sel_clicked() {

	// Slot to react to select file button
	TString filename = get_filename();

	text_add_file->SetText( filename );
	on_add_clicked();

	return;

}

void MiniballGUI::on_add_clicked() {

	// Slot to react to add file button
	TGString filename = text_add_file->GetText();

	run_list_box->AddEntrySort( filename, filelist.size() + 1 );
	run_list_box->Layout();

	filelist.push_back( filename.GetString() );
	filestatus.push_back( true );

}

void MiniballGUI::on_del_clicked() {

	// Cleanup the selected entries
	run_selected->Clear();

	// Slot to react to remove file button
	if( run_list_box->GetSelected() < 0 ) {

		std::cout << "\nNo runs selected" << std::endl;

	}

	else if( run_list_box->GetMultipleSelections() ) {

		run_list_box->GetSelectedEntries( run_selected );
		TIter next( run_selected );

		while( TGLBEntry *ent = (TGLBEntry*)next() ) {

			filestatus.at( ent->EntryId() - 1 ) = false;
			run_list_box->RemoveEntry( ent->EntryId() );

		}

	}

	else {

		filestatus.at( run_list_box->GetSelected() - 1 ) = false;
		run_list_box->RemoveEntry( -1 );

	}

	run_list_box->Layout();

}

void MiniballGUI::SaveSetup( TString setupfile ) {

	TEnv *fSetup = new TEnv( setupfile );

	TString list_of_files = "";

	for( unsigned int i = 0; i < filelist.size(); i++ ) {

		if( !filestatus.at( i ) ) continue;

		list_of_files += filelist.at(i);
		list_of_files += " ";

	}

	fSetup->SetValue( "filelist", list_of_files );
	fSetup->SetValue( "force", check_force->IsOn() );
	fSetup->SetValue( "events", check_event->IsOn() );
	fSetup->SetValue( "ebis", check_ebis->IsOn() );
	fSetup->SetValue( "mbs", check_mbs->IsOn() );

	fSetup->WriteFile( setupfile );

}

void MiniballGUI::LoadSetup( TString setupfile ) {

	TEnv *fSetup = new TEnv( setupfile );
	fSetup->ReadFile( setupfile, kEnvLocal );

	TString list_of_files = fSetup->GetValue( "filelist", "" );
	std::vector <TString>().swap( filelist );
	std::vector <bool>().swap( filestatus );
	run_list_box->RemoveAll();

	std::stringstream ss;
	TString current_file;
	ss << list_of_files;
	ss >> current_file;

	while( !ss.eof() ) {

		filelist.push_back( current_file );
		filestatus.push_back( true );

		run_list_box->AddEntrySort( current_file, filelist.size() );

		ss >> current_file;

	}

	run_list_box->Layout();

	check_force->SetOn( fSetup->GetValue( "force", false ) );
	check_event->SetOn( fSetup->GetValue( "event", false ) );
	check_ebis->SetOn( fSetup->GetValue( "ebis", false ) );
	check_mbs->SetOn( fSetup->GetValue( "mbs", false ) );

}

void MiniballGUI::gui_convert(){
	
	//------------------------//
	// Run conversion to ROOT //
	//------------------------//
	MiniballMidasConverter conv_midas( myset );
	MiniballMbsConverter conv_mbs( myset );

	if( flag_mbs ) conv_mbs.AddProgressBar( prog_conv );
	else conv_midas.AddProgressBar( prog_conv );

	std::cout << "\n +++ Miniball Analysis:: processing MiniballMidasConverter +++" << std::endl;

	// Progress bar and filename
	std::string prog_format;
	TFile *rtest;
	std::ifstream ftest;
	TString name_input_file;
	TString name_output_file;
	
	// Check each file
	for( unsigned int i = 0; i < filelist.size(); i++ ){
			
		name_input_file = filelist.at(i);
		name_input_file = name_input_file( name_input_file.Last('/')+1,
								name_input_file.Length() - name_input_file.Last('/')-1 );
		if( name_input_file.Contains('.') )
			name_input_file = name_input_file( 0, name_input_file.Last('.') );

		if( flag_source ) name_output_file = name_input_file + "_source.root";
		else name_output_file = name_input_file + ".root";
		
		name_output_file = datadir_name + "/" + name_output_file;
		name_input_file = filelist.at(i);

		force_convert.push_back( false );
		
		// Skip the file if it's deleted
		if( !filestatus.at(i) ) continue;

		// If input doesn't exist, skip it
		ftest.open( name_input_file.Data() );
		if( !ftest.is_open() ) {

			std::cerr << name_input_file << " does not exist" << std::endl;
			continue;

		}
		else ftest.close();
		
		// If input doesn't exist, skip it
		ftest.open( name_input_file.Data() );
		if( !ftest.is_open() ) {
			
			std::cerr << name_input_file << " does not exist" << std::endl;
			continue;
			
		}
		else ftest.close();

		// If output doesn't exist, we have to convert it anyway
		// The convert flag will force it to be converted
		ftest.open( name_output_file );
		if( !ftest.is_open() ) force_convert.at(i) = true;
		else {
			
			ftest.close();
			rtest = new TFile( name_output_file );
			if( rtest->IsZombie() ) force_convert.at(i) = true;
			if( !flag_convert && !force_convert.at(i) )
				std::cout << name_output_file << " already converted" << std::endl;
			rtest->Close();
			
		}

		if( flag_convert || force_convert.at(i) ) {
			
			std::cout << name_input_file << " --> ";
			std::cout << name_output_file << std::endl;
			
			prog_format  = "Converting ";
			prog_format += name_input_file( name_input_file.Last('/') + 1,
					name_input_file.Length() - name_input_file.Last('/') ).Data();
			prog_format += ": %.0f%%";
			prog_conv->ShowPosition( true, false, prog_format.data() );

			// Open file and covert data to ROOT
			if( flag_mbs ) {
		
				if( flag_source ) conv_mbs.SourceOnly();
				if( flag_ebis ) conv_mbs.EBISOnly();
				conv_mbs.SetOutput( name_output_file.Data() );
				conv_mbs.AddCalibration( mycal );
				conv_mbs.MakeTree();
				conv_mbs.MakeHists();
				conv_mbs.ConvertFile( name_input_file.Data() );

			}
			else {
				
				if( flag_source ) conv_midas.SourceOnly();
				if( flag_ebis ) conv_midas.EBISOnly();
				conv_midas.SetOutput( name_output_file.Data() );
				conv_midas.AddCalibration( mycal );
				conv_midas.MakeTree();
				conv_midas.MakeHists();
				conv_midas.ConvertFile( name_input_file.Data() );
				
			}

			prog_format  = "Converter complete";
			prog_conv->ShowPosition( true, false, prog_format.data() );

			// Time sorting
			if( !flag_source ) {

				prog_format  = "Time ordering ";
				prog_format += name_input_file( name_input_file.Last('/') + 1,
											   name_input_file.Length() - name_input_file.Last('/') ).Data();
				prog_format += ": %.0f%%";
				prog_sort->ShowPosition( true, false, prog_format.data() );

				if( flag_mbs ) {
					conv_mbs.AddProgressBar( prog_sort );
					conv_mbs.BuildMbsIndex();
					if( myset->GetMbsEventMode() )
						conv_mbs.SortTree(false);
					conv_mbs.SortTree();
				}
				else {
					conv_midas.AddProgressBar( prog_sort );
					conv_midas.SortTree();
				}

				
				prog_format  = "Time ordering complete";
				prog_conv->ShowPosition( true, false, prog_format.data() );

			}

			// Close file
			if( flag_mbs ) conv_mbs.CloseOutput();
			else conv_midas.CloseOutput();

		}
		
		// Update everything
		gSystem->ProcessEvents();
		
	}
	
	return;
	
}

void MiniballGUI::gui_build(){
	
	//-----------------------//
	// Physics event builder //
	//-----------------------//
	MiniballEventBuilder eb( myset );
	eb.AddProgressBar( prog_evnt );
	std::cout << "\n +++ Miniball Analysis:: processing MiniballEventBuilder +++" << std::endl;

	// Update everything
	gSystem->ProcessEvents();

	// Progress bar and filename
	std::string prog_format;
	TFile *rtest;
	std::ifstream ftest;
	TString name_input_file;
	TString name_output_file;
	
	// Update calibration file if given
	if( mycal->InputFile() != "dummy" )
		eb.AddCalibration( mycal );

	// Do event builder for each file individually
	for( unsigned int i = 0; i < filelist.size(); i++ ){

		name_input_file = filelist.at(i);
		name_input_file = name_input_file( name_input_file.Last('/')+1,
											name_input_file.Length() - name_input_file.Last('/')-1 );
		if( name_input_file.Contains('.') )
			name_input_file = name_input_file( 0, name_input_file.Last('.') );

		name_output_file = datadir_name + "/" + name_input_file + "_events.root";
		name_input_file = datadir_name + "/" + name_input_file + ".root";

		// Skip the file if it's deleted
		if( !filestatus.at(i) ) continue;

		// If input doesn't exist, skip it
		ftest.open( name_input_file.Data() );
		if( !ftest.is_open() ) {

			std::cerr << name_input_file << " does not exist" << std::endl;
			continue;

		}
		else {
			
			ftest.close();
			
		}

		// We need to do event builder if we just converted it
		// specific request to do new event build with -e
		// this is useful if you need to add a new calibration
		if( flag_convert || force_convert.at(i) || flag_events )
			force_events = true;

		// If it doesn't exist, we have to sort it anyway
		else {

			ftest.open( name_output_file );
			if( !ftest.is_open() ) force_events = true;
			else {

				ftest.close();
				rtest = new TFile( name_output_file );
				if( rtest->IsZombie() ) force_events = true;
				if( !force_events )
					std::cout << name_output_file << " already built" << std::endl;
				rtest->Close();

			}

		}

		if( force_events ) {

			std::cout << name_input_file << " --> ";
			std::cout << name_output_file << std::endl;

			prog_format  = "Building ";
			prog_format += name_input_file( name_input_file.Last('/') + 1,
						name_input_file.Length() - name_input_file.Last('/') ).Data();
			prog_format += ": %.0f%%";
			prog_evnt->ShowPosition( true, false, prog_format.data() );

			eb.SetInputFile( name_input_file.Data() );
			eb.SetOutput( name_output_file.Data() );
			eb.BuildEvents();
			eb.CloseOutput();

			force_events = false;

		}

		prog_format  = "EventBuilder complete";
		prog_evnt->ShowPosition( true, false, prog_format.data() );

		// Update everything
		gSystem->ProcessEvents();

	}
	
	return;
	
}

void MiniballGUI::gui_hist(){
	
	//------------------------------//
	// Finally make some histograms //
	//------------------------------//
	MiniballHistogrammer hist( myrea, myset );
	hist.AddProgressBar( prog_hist );
	std::cout << "\n +++ Miniball Analysis:: processing MiniballHistogrammer +++" << std::endl;

	// Update everything
	gSystem->ProcessEvents();

	// Progress bar and filename
	std::string prog_format;
	std::ifstream ftest;
	TString name_input_file;
	TString name_output_file;
	
	prog_format  = "Histogramming: %.0f%%";
	prog_hist->ShowPosition( true, false, prog_format.data() );
	
	name_output_file = text_out_file->GetText();
	if( name_output_file == "" ) name_output_file = "output.root";
	hist.SetOutput( name_output_file.Data() );
	std::vector<std::string> name_hist_files;

	// We are going to chain all the event files now
	for( unsigned int i = 0; i < filelist.size(); i++ ){

		// Skip the file if it's deleted
		if( !filestatus.at(i) ) continue;
		
		name_input_file = filelist.at(i);
		name_input_file = name_input_file( name_input_file.Last('/')+1,
										  name_input_file.Length() - name_input_file.Last('/')-1 );
		if( name_input_file.Contains('.') )
			name_input_file = name_input_file( 0, name_input_file.Last('.') );
		name_input_file = datadir_name + "/" + name_input_file + "_events.root";
		
		// Test if the input file exists
		ftest.open( name_input_file.Data() );
		if( !ftest.is_open() ) {
			
			std::cerr << name_input_file << " does not exist" << std::endl;
			continue;
			
		}
		else ftest.close();

		name_hist_files.push_back( name_input_file.Data() );

	}

	hist.SetInputFile( name_hist_files );
	hist.FillHists();
	hist.CloseOutput();
	
	prog_format  = "Histogramming complete";
	prog_hist->ShowPosition( true, false, prog_format.data() );

	
	// Update everything
	gSystem->ProcessEvents();
	return;
	
}

void MiniballGUI::on_sort_clicked() {

	// Settings files, etc
	std::string name_set_file = text_set_file->GetText();
	std::string name_cal_file = text_cal_file->GetText();
	std::string name_rea_file = text_rea_file->GetText();

	if( name_set_file == "" ) name_set_file = "dummy";
	if( name_cal_file == "" ) name_cal_file = "dummy";
	if( name_rea_file == "" ) name_rea_file = "dummy";

	myset = std::make_shared<MiniballSettings>( name_set_file );
	mycal = std::make_shared<MiniballCalibration>( name_cal_file, myset );
	if( flag_mbs ) mycal->SetDefaultQint();
	mycal->ReadCalibration();
	myrea = std::make_shared<MiniballReaction>( name_rea_file, myset );
	
	// select what steps of the analysis to be forced
	force_events = false;
	flag_source = check_source->IsOn();
	flag_convert = check_force->IsOn();
	flag_events = check_event->IsOn();
	flag_ebis = check_ebis->IsOn();
	flag_mbs = check_mbs->IsOn();
	datadir_name = text_out_dir->GetText();

	//------------------//
	// Run the analysis //
	//------------------//
	gui_convert();
	gui_build();
	gui_hist();
	std::cout << "\n\nFinished!\n";
	
}

MyDialog::MyDialog( const TGWindow *p, const TGWindow *main, TString msg, bool &ans ) {
	
	// Default answer is false
	answer = false;
	
	fDialog = new TGTransientFrame( p, main, 800, 100, kVerticalFrame );
	frame_button = new TGHorizontalFrame( fDialog, 240, 60 );
	
	dialog_msg = new TGLabel( fDialog, msg );
	fDialog->AddFrame( dialog_msg, new TGLayoutHints( kLHintsTop | kLHintsExpandY, 5, 5, 5, 5) );
	
	but_yes = new TGTextButton( frame_button, " &Yes ", 1 );
	but_yes->Connect( "Clicked()", "MyDialog", this, "SayYes()" );
	but_yes->Associate( fDialog );
	frame_button->AddFrame( but_yes, new TGLayoutHints( kLHintsLeft | kLHintsExpandX, 4, 4, 4, 4 ) );
	
	but_no = new TGTextButton( frame_button, " &No ", 1 );
	but_no->Connect( "Clicked()", "MyDialog", this, "SayNo()" );
	but_no->Associate( fDialog );
	frame_button->AddFrame( but_no, new TGLayoutHints( kLHintsLeft | kLHintsExpandX, 4, 4, 4, 4 ) );
	
	frame_button->Resize( 100, but_no->GetDefaultHeight() + 4 );
	fDialog->AddFrame( frame_button, new TGLayoutHints( kLHintsBottom | kLHintsCenterX | kLHintsExpandY, 5, 5, 5, 5 ) );

	fDialog->MapSubwindows();
	fDialog->Resize( fDialog->GetDefaultSize() );
	
	fDialog->MapWindow();

	gClient->WaitFor( fDialog );

	ans = answer;
	
}

MyDialog::~MyDialog() {

	delete fDialog;
	delete but_yes;
	delete but_no;
	delete dialog_msg;
	delete frame_button;
	
	delete fDialog;
	
}

void MyDialog::SayYes() {
	
	answer = true;
	fDialog->SendCloseMessage();
	
}

void MyDialog::SayNo() {
	
	answer = false;
	fDialog->SendCloseMessage();
	
}


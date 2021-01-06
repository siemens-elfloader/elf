#pragma once


namespace brow {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	protected: 
	private: System::Windows::Forms::Button^  button1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(41, 27);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(239, 183);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(168, 242);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 271);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->richTextBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);

		}
#define RBC_PORT 80
#define RBC_ADDR "127.0.0.1"
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
int rc;
WSADATA WSAData;
rc = WSAStartup(MAKEWORD(1, 1), &WSAData);
if(rc != 0) return FALSE;

struct sockaddr_in srv_address;
int namelen;

SendSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if(SendSocket != INVALID_SOCKET) {
memset(&srv_address,0,sizeof(SOCKADDR_IN));
srv_address.sin_addr.S_un.S_addr=INADDR_ANY;
srv_address.sin_family = AF_INET;
srv_address.sin_port = 0;
}
if(bind(SendSocket, (SOCKADDR *) &srv_address, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
closesocket(SendSocket);
return FALSE;
} else {
namelen=sizeof(SOCKADDR_IN);
getsockname(SendSocket,(SOCKADDR *)&srv_address,&namelen);
return TRUE;
}

			 }
	};
}


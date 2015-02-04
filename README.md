#Inspire

**Inspire** is a ui layout library for win32 platform.

**Inspire** aims at building ui layout for win32 applications easily.

When you build a project with Inspire, and you can use a button like:

```
// init button and set callback when button clicked
InitControl( this, m_btnOK, L"btnOK", SetPressFunc(&CUIMessageBox::OnBtnOK) ) ;
// make sure the button named "btnOK" is existed.
INSPIRE_ASSERT( m_btnOK, L"Cannot find button: %s", L"btnOK" ) ;

// let button can be click
m_btnOK->Enable() ;

// let button hide
m_btnOK->ShowWindow( false ) ;
```

Inpsire comes with some modules:

* **Log**   module : with serveral levels: fatal, error, debug, info... is may not thread safety.
* **XML**   module : which is inspired by rapidxml, and I abstracted interfaces like IXMLDocument, IXMLElement,
            IXMLNode...and so on.
* **Util**  module: includes memory pool, free list, char converter...
* **Controls**  module : StaticText, CheckBox, ComboBox, Button, EditBox...etc.

A series of components will be supported when it finished, such as Inspire libaray, UIDesigner...etc.

Welcome to fork and improve **Inspire**.

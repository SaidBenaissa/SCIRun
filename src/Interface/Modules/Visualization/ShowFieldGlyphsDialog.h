/*
For more information, please see: http://software.sci.utah.edu

The MIT License

Copyright (c) 2015 Scientific Computing and Imaging Institute,
University of Utah.

License for the specific language governing rights and limitations under
Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef INTERFACE_MODULES_SHOW_FIELD_GLYPHS_DIALOG_H
#define INTERFACE_MODULES_SHOW_FIELD_GLYPHS_DIALOG_H

#include "Interface/Modules/Visualization/ui_ShowFieldGlyphs.h"
#include <Interface/Modules/Base/ModuleDialogGeneric.h>
#include <Interface/Modules/Visualization/ShowFieldGlyphsVectorTabDialog.h>
#include <Interface/Modules/Visualization/ShowFieldGlyphsScalarTabDialog.h>
#include <Interface/Modules/Visualization/ShowFieldGlyphsTensorTabDialog.h>
#include <Interface/Modules/Visualization/share.h>

namespace SCIRun {
  namespace Gui {

    class ShowFieldGlyphsScalarTabDialog;
    class ShowFieldGlyphsVectorTabDialog;
    class ShowFieldGlyphsTensorTabDialog;

    class SCISHARE ShowFieldGlyphsDialog : public ModuleDialogGeneric,
      public Ui::ShowFieldGlyphsDialog
    {
      Q_OBJECT

    public:
      ShowFieldGlyphsDialog(const std::string& name,
        SCIRun::Dataflow::Networks::ModuleStateHandle state,
        QWidget* parent = 0);
      virtual void createStartupNote() override;

    protected:
      virtual void pullSpecial() override;

      private Q_SLOTS:
      void push();
      void pushColor();
      void assignDefaultMeshColor();

    private:
      QColor defaultMeshColor_;
      ShowFieldGlyphsScalarTabDialog* scalarTab_;
      ShowFieldGlyphsVectorTabDialog* vectorTab_;
      ShowFieldGlyphsTensorTabDialog* tensorTab_;


      int vectorTabIndex_;
      int scalarTabIndex_;
      int tensorTabIndex_;

      void checkTabs();
      void setupScalarsTab();
      void setupVectorsTab();
      void setupTensorsTab();
    };

  }
}

#endif //INTERFACE_MODULES_SHOW_FIELD_GLYPHS_DIALOG_H

#include "function_curve_parameter_controller.h"
#include <assert.h>

namespace Shared {

FunctionCurveParameterController::FunctionCurveParameterController(InteractiveCurveViewRange * graphRange, CurveViewCursor * cursor) :
  ViewController(nullptr),
  m_goToCell(PointerTableCellWithChevron((char*)"Aller a")),
  m_selectableTableView(SelectableTableView(this, this, Metric::CommonTopMargin, Metric::CommonRightMargin,
    Metric::CommonBottomMargin, Metric::CommonLeftMargin)),
  m_goToParameterController(GoToParameterController(this, graphRange, cursor)),
  m_function(nullptr)
{
}

View * FunctionCurveParameterController::view() {
  return &m_selectableTableView;
}

void FunctionCurveParameterController::didBecomeFirstResponder() {
  m_selectableTableView.selectCellAtLocation(0, 0);
  app()->setFirstResponder(&m_selectableTableView);
}

bool FunctionCurveParameterController::handleGotoSelection() {
  if (m_function == nullptr) {
    return false;
  }
  m_goToParameterController.setFunction(m_function);
  StackViewController * stack = (StackViewController *)parentResponder();
  stack->push(&m_goToParameterController);
  return true;
}

KDCoordinate FunctionCurveParameterController::cellHeight() {
  return Metric::ParameterCellHeight;
}

void FunctionCurveParameterController::setFunction(Function * function) {
  m_function = function;
}

}
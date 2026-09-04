#ifndef SourceLabRunAction_h
#define SourceLabRunAction_h 1

#include "G4UserRunAction.hh"

namespace SourceLab
{
class SourceLabDetectorConstruction;
class SourceLabEventAction;

class SourceLabRunAction : public G4UserRunAction
{
  public:
    SourceLabRunAction(SourceLabDetectorConstruction* detectorConstruction = nullptr,
      SourceLabEventAction* eventAction = nullptr);
    ~SourceLabRunAction() override = default;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

  private:
    SourceLabDetectorConstruction* fDetectorConstruction = nullptr;
    SourceLabEventAction* fEventAction = nullptr;
};

}  // namespace SourceLab

#endif

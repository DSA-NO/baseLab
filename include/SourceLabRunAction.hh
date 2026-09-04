#ifndef SourceLabRunAction_h
#define SourceLabRunAction_h 1

#include "G4UserRunAction.hh"

namespace SourceLab
{
class SourceLabDetectorConstruction;

class SourceLabRunAction : public G4UserRunAction
{
  public:
    explicit SourceLabRunAction(SourceLabDetectorConstruction* detectorConstruction = nullptr);
    ~SourceLabRunAction() override = default;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

  private:
    SourceLabDetectorConstruction* fDetectorConstruction = nullptr;
};

}  // namespace SourceLab

#endif

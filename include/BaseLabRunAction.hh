#ifndef BaseLabRunAction_h
#define BaseLabRunAction_h 1

#include "G4UserRunAction.hh"

namespace BaseLab
{
class BaseLabDetectorConstruction;

class BaseLabRunAction : public G4UserRunAction
{
  public:
    explicit BaseLabRunAction(BaseLabDetectorConstruction* detectorConstruction = nullptr);
    ~BaseLabRunAction() override = default;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

  private:
    BaseLabDetectorConstruction* fDetectorConstruction = nullptr;
};

}  // namespace BaseLab

#endif

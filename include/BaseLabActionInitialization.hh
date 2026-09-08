#ifndef BaseLabActionInitialization_h
#define BaseLabActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

#include "globals.hh"

namespace BaseLab
{
class BaseLabDetectorConstruction;

class BaseLabActionInitialization : public G4VUserActionInitialization
{
  public:
    explicit BaseLabActionInitialization(BaseLabDetectorConstruction* detectorConstruction = nullptr,
      const G4String& emModel = "option4",
      G4bool enableRadioactiveDecay = false);
    ~BaseLabActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build() const override;

  private:
    BaseLabDetectorConstruction* fDetectorConstruction = nullptr;
    G4String fEmModel;
    G4bool fEnableRadioactiveDecay = false;
};

}  // namespace BaseLab

#endif

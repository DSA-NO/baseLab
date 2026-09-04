#ifndef BaseLabActionInitialization_h
#define BaseLabActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

namespace BaseLab
{
class BaseLabDetectorConstruction;

class BaseLabActionInitialization : public G4VUserActionInitialization
{
  public:
    explicit BaseLabActionInitialization(BaseLabDetectorConstruction* detectorConstruction = nullptr);
    ~BaseLabActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build() const override;

  private:
    BaseLabDetectorConstruction* fDetectorConstruction = nullptr;
};

}  // namespace BaseLab

#endif

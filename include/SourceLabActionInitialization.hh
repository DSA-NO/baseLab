#ifndef SourceLabActionInitialization_h
#define SourceLabActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

namespace SourceLab
{
class SourceLabDetectorConstruction;

class SourceLabActionInitialization : public G4VUserActionInitialization
{
  public:
    explicit SourceLabActionInitialization(SourceLabDetectorConstruction* detectorConstruction = nullptr);
    ~SourceLabActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build() const override;

  private:
    SourceLabDetectorConstruction* fDetectorConstruction = nullptr;
};

}  // namespace SourceLab

#endif

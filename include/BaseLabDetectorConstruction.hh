#ifndef BaseLabDetectorConstruction_h
#define BaseLabDetectorConstruction_h 1

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;

namespace BaseLab
{
class BaseLabDetectorMessenger;

struct DetectorConfig
{
  G4double worldSize = 2.0 * m;
  G4double phantomHalfX = 0.5 * m;
  G4double phantomHalfY = 0.5 * m;
  G4double phantomHalfZ = 0.5 * m;
  G4double sampleDepth = 10.0 * cm;
  G4double sampleRadius = 5.0 * cm;
  G4double sampleThickness = 1.0 * mm;
};

class BaseLabDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    BaseLabDetectorConstruction();
    ~BaseLabDetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

    void SetConfig(const DetectorConfig& config);
    DetectorConfig GetConfig() const;

    void SetWorldSize(G4double worldSize);
    void SetPhantomHalfSize(G4double x, G4double y, G4double z);
    void SetSampleDepth(G4double depth);
    void SetSampleSize(G4double radius, G4double thickness);

    G4double GetWorldSize() const;
    G4double GetSampleDepth() const;
    G4double GetSampleRadius() const;
    G4double GetSampleThickness() const;
    void PrintConfig() const;

  private:
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    BaseLabDetectorMessenger* fMessenger = nullptr;
    G4bool fCheckOverlaps = true;

    DetectorConfig fConfig;
    G4LogicalVolume* fSampleLog = nullptr;
};

}  // namespace BaseLab

#endif

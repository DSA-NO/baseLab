#ifndef SourceLabEventAction_h
#define SourceLabEventAction_h 1

#include "G4SystemOfUnits.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"

namespace SourceLab
{
class SourceLabEventAction : public G4UserEventAction
{
  public:
    SourceLabEventAction();
    ~SourceLabEventAction() override = default;

    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;

    void Reset();
    G4double GetTotalEnergyDeposit() const;

  private:
    G4double fTotalEnergyDeposit = 0.0;
};

}  // namespace SourceLab

#endif

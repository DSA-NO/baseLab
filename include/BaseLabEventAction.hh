#ifndef BaseLabEventAction_h
#define BaseLabEventAction_h 1

#include "G4SystemOfUnits.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"

namespace BaseLab
{
class BaseLabEventAction : public G4UserEventAction
{
  public:
    BaseLabEventAction();
    ~BaseLabEventAction() override = default;

    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;

    void Reset();
    G4double GetTotalEnergyDeposit() const;

  private:
    G4double fTotalEnergyDeposit = 0.0;
};

}  // namespace BaseLab

#endif

#include "BaseLabActionInitialization.hh"
#include "BaseLabDetectorConstruction.hh"

#include "FTFP_BERT.hh"
#include "G4RunManagerFactory.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

namespace
{
void PrintUsage()
{
  G4cout << " Usage: " << G4endl;
  G4cout << " baseLab [-b macro] [-v macro] [-t nThreads]" << G4endl;
  G4cout << "   -b macro  : batch mode, execute the given macro" << G4endl;
  G4cout << "   -v macro  : visualize, execute the macro, and keep the UI open" << G4endl;
  G4cout << "   -t N      : number of threads for multi-threaded builds" << G4endl;
  G4cout << "   (no args) : interactive session" << G4endl;
}
}  // namespace

int main(int argc, char** argv)
{
  G4String macro;
  G4String visMacro;

#ifdef G4MULTITHREADED
  G4int nThreads = 0;
#endif

  for (G4int i = 1; i < argc; ++i) {
    G4String arg = argv[i];
    if (arg == "-b") {
      if (i + 1 >= argc) {
        PrintUsage();
        return 1;
      }
      macro = argv[++i];
    }
    else if (arg == "-v") {
      if (i + 1 >= argc) {
        PrintUsage();
        return 1;
      }
      visMacro = argv[++i];
    }
#ifdef G4MULTITHREADED
    else if (arg == "-t") {
      if (i + 1 >= argc) {
        PrintUsage();
        return 1;
      }
      nThreads = std::atoi(argv[++i]);
    }
#endif
    else {
      PrintUsage();
      return 1;
    }
  }

  if (!macro.empty() && !visMacro.empty()) {
    G4cerr << "Error: -b and -v are mutually exclusive." << G4endl;
    PrintUsage();
    return 1;
  }

  G4UIExecutive* ui = nullptr;
  if (macro.empty()) {
    ui = new G4UIExecutive(argc, argv);
  }

  auto runManager = G4RunManagerFactory::CreateRunManager();
#ifdef G4MULTITHREADED
  if (nThreads > 0) {
    runManager->SetNumberOfThreads(nThreads);
  }
#endif

  auto detector = new BaseLab::BaseLabDetectorConstruction();
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new FTFP_BERT);
  runManager->SetUserInitialization(new BaseLab::BaseLabActionInitialization(detector));

  auto visManager = new G4VisExecutive;
  visManager->Initialize();

  auto* UImanager = G4UImanager::GetUIpointer();

  if (!macro.empty()) {
    UImanager->ApplyCommand("/control/execute " + macro);
  }
  else if (!visMacro.empty()) {
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    if (ui && ui->IsGUI()) {
      UImanager->ApplyCommand("/control/execute gui.mac");
    }
    UImanager->ApplyCommand("/control/execute " + visMacro);
    ui->SessionStart();
    delete ui;
  }
  else {
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    if (ui && ui->IsGUI()) {
      UImanager->ApplyCommand("/control/execute gui.mac");
    }
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;
  return 0;
}

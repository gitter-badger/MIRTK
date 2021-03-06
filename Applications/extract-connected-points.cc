/*
 * Medical Image Registration ToolKit (MIRTK)
 *
 * Copyright 2013-2015 Imperial College London
 * Copyright 2013-2015 Andreas Schuh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <mirtkCommon.h>
#include <mirtkOptions.h>

#include <mirtkPointSetUtils.h>

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkCleanPolyData.h>

using namespace mirtk;


// =============================================================================
// Help
// =============================================================================

// -----------------------------------------------------------------------------
void PrintHelp(const char *name)
{
  cout << endl;
  cout << "Usage: " << name << " <input> <output> [options]" << endl;
  cout << endl;
  cout << "Description:" << endl;
  cout << "  Extract (largest) connected components of the input point set." << endl;
  cout << "  The connected components are sorted by size, where the largest" << endl;
  cout << "  connected component has index 0." << endl;
  cout << endl;
  cout << "Arguments:" << endl;
  cout << "  input    Input point set." << endl;
  cout << "  output   Output point set." << endl;
  cout << endl;
  cout << "Optional arguments:" << endl;
  cout << "  -m <m>          Index of first connected component to extract. (default: 0)" << endl;
  cout << "  -n <n>          Extract (at most) n components. (default: 1)" << endl;
  cout << "  -[no]compress   Write XML VTK with compression enabled/disabled. (default: on)" << endl;
  cout << "  -ascii          Write legacy VTK in ASCII  format. (default: off)" << endl;
  cout << "  -binary         Write legacy VTK in binary format. (default: on)" << endl;
  PrintStandardOptions(cout);
  cout << endl;
}

// =============================================================================
// Main
// =============================================================================

// -----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  EXPECTS_POSARGS(2);

  const char *input_name  = POSARG(1);
  const char *output_name = POSARG(2);

  int  m        = 0;
  int  n        = 1;
  bool compress = true;
  bool ascii    = false;

  for (ALL_OPTIONS) {
    if      (OPTION("-m")) PARSE_ARGUMENT(m);
    else if (OPTION("-n")) PARSE_ARGUMENT(n);
    else if (OPTION("-binary"))     ascii    = false;
    else if (OPTION("-ascii"))      ascii    = true;
    else if (OPTION("-compress"))   compress = true;
    else if (OPTION("-nocompress")) compress = false;
    else HANDLE_STANDARD_OR_UNKNOWN_OPTION();
  }

  vtkSmartPointer<vtkPolyData> input = ReadPolyData(input_name);

  if (verbose) cout << "Analyzing connected components...", cout.flush();
  vtkNew<vtkPolyDataConnectivityFilter> lcc;
  SetVTKInput(lcc, input);
  lcc->SetExtractionModeToAllRegions();
  lcc->Update();
  lcc->SetExtractionModeToSpecifiedRegions();
  const int npoints  = static_cast<int>(input->GetNumberOfPoints());
  const int nregions = lcc->GetNumberOfExtractedRegions();
  if (verbose) {
    cout << " done\n";
    cout << "No. of input points:         " << npoints << "\n";
    cout << "No. of connected components: " << nregions << "\n";
    cout.flush();
  }

  if (m >= nregions) {
    FatalError("Start index -m is greater or equal than the total no. of components!");
  }
  if (m + n > nregions) n = nregions - m;

  if (verbose) cout << "Extracting " << n << " components starting with component " << m+1 << "...", cout.flush();
  for (int i = 0; i < nregions; ++i) {
    lcc->DeleteSpecifiedRegion(i);
  }
  for (int i = m; i < m + n; ++i) {
    lcc->AddSpecifiedRegion(i);
  }
  lcc->Update();
  if (verbose) cout << " done" << endl;

  if (verbose) cout << "Cleaning extracted components...", cout.flush();
  vtkNew<vtkCleanPolyData> cleaner;
  SetVTKInput(cleaner, lcc->GetOutput());
  cleaner->Update();
  if (verbose) cout << " done" << endl;

  if (!WritePointSet(output_name, cleaner->GetOutput(), compress, ascii)) {
    FatalError("Failed to write components to file " << output_name);
  }

  return 0;
}

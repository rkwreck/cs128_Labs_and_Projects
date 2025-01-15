#include "utilities.hpp"
#include <cmath>

// Feel free to edit, this file is not graded

using namespace std;

double PitchToFrequency(int pitch) {
  return 440.0f * std::pow(2.0f, (pitch - 69) / 12.0f);
}

float mixHarmonics(float frequency,
                   int sampleRate,
                   int i,
                   const std::vector<float>& harmonicWeights) {
  float sample = 0.0;
  for (int h = 0; h < harmonicWeights.size(); ++h) {
    // (h + 1) represents the harmonic number; harmonicWeights[h] is the
    // amplitude of the harmonic
    sample += sin(2 * M_PI * (h + 1) * frequency * i / sampleRate) *
              harmonicWeights[h];
  }
  return sample;
}
void GenerateMP3(vector<Note> melody, const string& file_name) {
  // Initialize LAME library
  lame_global_flags* lame = lame_init();
  if (lame == nullptr) {
    throw std::runtime_error("lame didn't init");
  }
  lame_set_num_channels(lame, 1);       // Mono audio
  lame_set_in_samplerate(lame, 44100);  // Sample rate
  lame_set_VBR(lame, vbr_default);      // Variable Bit Rate (VBR) encoding
  if (lame_init_params(lame) < 0) {
    lame_close(lame);
    throw std::runtime_error("Error: Failed to initialize LAME parameters.");
  }

  // Create MP3 file
  FILE* mp3File = fopen(file_name.c_str(), "wb");
  if (mp3File == nullptr) {
    lame_close(lame);
    throw std::runtime_error("Error: Failed to create output file.");
  }

  // Add each note to the MP3
  for (const auto& note : melody) {
    int pitch = note.pitch;
    float duration = note.duration;
    float frequency = PitchToFrequency(pitch);
    int numSamples = duration * lame_get_in_samplerate(lame);

    // Generate PCM audio data for the note
    std::vector<float> pcmData(numSamples);
    for (int i = 0; i < numSamples; ++i) {
      std::vector<float> guitarHarmonics = {
          1.0,
          0.6,
          0.3,
          0.15,
          0.1,
          0.05};  // Strong fundamental, decreasing harmonics
      std::vector<float> pianoHarmonics = {
          1.0, 0.7, 0.5, 0.3, 0.2, 0.1};  // More even harmonic distribution
      std::vector<float> fluteHarmonics = {1.0, 0.05, 0.01};
      std::vector<float> stringHarmonics = {
          1.0, 0.8, 0.6, 0.4, 0.3, 0.2, 0.1, 0.05};

      pcmData[i] = mixHarmonics(
          frequency,
          lame_get_in_samplerate(lame),
          i,
          fluteHarmonics);  // Change as needed
                            // pcmData[i] = sin(2 * M_PI * frequency * i /
                            // lame_get_in_samplerate(lame));
    }

    // Encode PCM data to MP3
    unsigned char mp3Buffer[8192];  // Buffer for MP3 data
    int mp3OutputSize = lame_encode_buffer_ieee_float(lame,
                                                      pcmData.data(),
                                                      nullptr,
                                                      numSamples,
                                                      mp3Buffer,
                                                      sizeof(mp3Buffer));

    // Write encoded MP3 data to file
    fwrite(mp3Buffer, 1, mp3OutputSize, mp3File);
  }

  // Flush and close MP3 file
  unsigned char mp3Buffer[4096];  // Buffer for MP3 data
  int mp3OutputSize = lame_encode_flush(lame, mp3Buffer, sizeof(mp3Buffer));
  fwrite(mp3Buffer, 1, mp3OutputSize, mp3File);
  fclose(mp3File);

  // Clean up LAME resources
  lame_close(lame);

  std::cout << "MP3 file generated: " << std::endl;
}
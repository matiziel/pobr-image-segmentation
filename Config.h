//
// Created by mateusz on 19.01.23.
//

#ifndef POBR_IMAGE_SEGMENTATION_CONFIG_H
#define POBR_IMAGE_SEGMENTATION_CONFIG_H

class Config {
public:
    struct LetterConfig {
        double M1Min, M1Max;
        double M2Min, M2Max;
        double M3Min, M3Max;
        double M4Min, M4Max;
        double M7Min, M7Max;

        static LetterConfig GetLetterLConfig() {
            return LetterConfig(
                    0.2298, 0.29154,
                    0.0, 0.02174,
                    0.0, 0.0,
                    0.0, 0.0,
                    0.0119, 0.015814);
        }

        static LetterConfig GetLetterIConfig() {
            return LetterConfig(
                    0.17094, 0.1896,
                    0.00018, 0.00438,
                    0.0, 0.0,
                    0.0, 0.0,
                    0.006307, 0.00895);
        }

        static LetterConfig GetLetterDOTConfig() {
            return LetterConfig(
                    0.1594, 0.1889,
                    0.0, 0.010358,
                    0.0, 0.0,
                    0.0, 0.0,
                    0.006307, 0.006381);
        }

        static LetterConfig GetLetterDConfig() {
            return LetterConfig(
                    0.18749, 0.216628,
                    0.0, 0.004254,
                    0.0, 0.0,
                    0.0, 0.0,
                    0.008785, 0.010669);
        }

        static LetterConfig GetWordLIConfig() {
            return LetterConfig(
                    0.4479, 0.44791,
                    0.11717, 0.11718,
                    0.0, 0.0,
                    0.0, 0.0,
                    0.020861, 0.020862);
        }

        static LetterConfig GetWordIDConfig() {
            return LetterConfig(
                    0.33787, 0.33788,
                    0.065157, 0.065158,
                    0.0, 0.0,
                    0.0, 0.0,
                    0.012250, 0.012251);
        }

        static LetterConfig GetWordLIDConfig() {
            return LetterConfig(
                    0.33937, 0.33988,
                    0.047814, 0.0478234,
                    0.0, 0.0,
                    0.0, 0.0,
                    0.016837, 0.016926);
        }

        static LetterConfig GetWordLIDLConfig() {
            return LetterConfig(
                    0.38567, 0.6995,
                    0.069017, 0.40903,
                    0.0, 9.93957e+08,
                    0.0, 1.11406e+08,
                    0.016015, 0.02427);
        }

        LetterConfig(const LetterConfig &config) {
            *this = config;
        }

    private:
        LetterConfig(double M1Min, double M1Max,
                     double M2Min, double M2Max,
                     double M3Min, double M3Max,
                     double M4Min, double M4Max,
                     double M7Min, double M7Max) {
            this->M1Min = M1Min;
            this->M1Max = M1Max;
            this->M2Min = M2Min;
            this->M2Max = M2Max;
            this->M3Min = M3Min;
            this->M3Max = M3Max;
            this->M4Min = M4Min;
            this->M4Max = M4Max;
            this->M7Min = M7Min;
            this->M7Max = M7Max;
        }
    };

    Config() :
            L(LetterConfig::GetLetterLConfig()),
            I(LetterConfig::GetLetterIConfig()),
            D(LetterConfig::GetLetterDConfig()),
            DOT(LetterConfig::GetLetterDOTConfig()),
            LI(LetterConfig::GetWordLIConfig()),
            ID(LetterConfig::GetWordIDConfig()),
            LID(LetterConfig::GetWordLIDConfig()),
            LIDL(LetterConfig::GetWordLIDLConfig()) {}

    const LetterConfig L;
    const LetterConfig I;
    const LetterConfig DOT;
    const LetterConfig D;
    const LetterConfig LI;
    const LetterConfig ID;
    const LetterConfig LID;
    const LetterConfig LIDL;

};

#endif //POBR_IMAGE_SEGMENTATION_CONFIG_H

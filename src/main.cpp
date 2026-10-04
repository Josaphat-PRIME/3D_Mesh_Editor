#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void parsePLY(const std::string& filename,
              std::vector<std::vector<float>>& V,
              std::vector<std::vector<int>>& F)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Erreur : impossible d'ouvrir " << filename << std::endl;
        return;
    }

    std::string ligne;
    int nbVertex = 0;
    int nbFace = 0;

    // Etape A : lire le header jusqu'a end_header
    while (std::getline(file, ligne)) {
        std::istringstream iss(ligne);
        std::string mot;
        iss >> mot;

        if (mot == "element") {
            std::string type;
            int n;
            iss >> type >> n;
            if (type == "vertex") nbVertex = n;
            else if (type == "face") nbFace = n;
        }

        if (ligne == "end_header") {
            break;
        }
    }

    // Etape B : lire les nbVertex lignes de sommets
    for (int i = 0; i < nbVertex; ++i) {
        std::getline(file, ligne);
        std::istringstream iss(ligne);
        float x, y, z;
        iss >> x >> y >> z;
        V.push_back({x, y, z});
    }

    // Etape C : lire les nbFace lignes de faces
    for (int i = 0; i < nbFace; ++i) {
        std::getline(file, ligne);
        std::istringstream iss(ligne);
        int count;
        iss >> count;
        std::vector<int> face;
        for (int j = 0; j < count; ++j) {
            int idx;
            iss >> idx;
            face.push_back(idx);
        }
        F.push_back(face);
    }

    file.close();
    std::cout << "Parsing termine : " << V.size() << " sommets, " << F.size() << " faces." << std::endl;
}

int main() {
    std::vector<std::vector<float>> V;
    std::vector<std::vector<int>> F;

    parsePLY("fan.ply", V, F);

    for (size_t i = 0; i < V.size(); ++i) {
        std::cout << "V" << i << " = (" << V[i][0] << ", " << V[i][1] << ", " << V[i][2] << ")" << std::endl;
    }
    for (size_t i = 0; i < F.size(); ++i) {
        std::cout << "F" << i << " = {" << F[i][0] << ", " << F[i][1] << ", " << F[i][2] << "}" << std::endl;
    }

    return 0;
}
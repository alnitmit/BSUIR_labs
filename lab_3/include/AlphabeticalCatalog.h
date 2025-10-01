#pragma once
#include "../include/Catalog.h"

class AlphabeticalCatalog : public Catalog {
public:
    LibraryCard** search(const std::string& query, int& resultCount) override;
};
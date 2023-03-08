#ifdef _GAS

#ifndef _GAS_H
#define _GAS_H

#pragma once

namespace gas
{
    void init();
    uint32_t read();
    uint32_t ppm(uint16_t raw);
}

#endif
#endif

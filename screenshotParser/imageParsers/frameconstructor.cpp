#include "frameconstructor.h"
#include <cmath>
#include <iostream>


FrameConstructor::FrameConstructor(uint32_t p_minCorner, uint32_t p_maxCorner):
    minCorner(p_minCorner),
    maxCorner(p_maxCorner)
{
}

std::list<BitMap *> FrameConstructor::construct(const BitMap& bmp, const std::pair<std::list<Line>, std::list<Line> >& lines)
{
    std::list<BitMap* > res;
    
    std::multimap<uint32_t, const Line&> h_lines;
    std::multimap<uint32_t, const Line&> v_lines;
    
    std::list<Line>::const_iterator h_begin = lines.first.begin();
    std::list<Line>::const_iterator h_end = lines.first.end();
    
    std::list<Line>::const_iterator v_begin = lines.second.begin();
    std::list<Line>::const_iterator v_end = lines.second.end();
    
    
    for (; h_begin != h_end; ++h_begin) {
        h_lines.insert(std::make_pair(h_begin->getY(), *h_begin));
    }
    
    for (; v_begin != v_end; ++v_begin) {
        v_lines.insert(std::make_pair(v_begin->getX(), *v_begin));
    }
    
    std::multimap<uint32_t, const Line&>::const_iterator top;
    std::multimap<uint32_t, const Line&>::const_iterator right;
    std::multimap<uint32_t, const Line&>::const_iterator left;
    std::multimap<uint32_t, const Line&>::const_iterator bottom;
    
    top = h_lines.begin();
    while (h_lines.size() > 1 && v_lines.size() > 1) {
        
        Line topLine = top->second;
        bool found = false;
        bottom = h_lines.upper_bound(top->first);
        while (!found && bottom != h_lines.end()) {
            Line bottomLine = bottom->second;
            if (bottomLine.getX() == topLine.getX() && topLine.getLength() == bottomLine.getLength()) {
                uint32_t begL = topLine.getX();
                if (maxCorner > begL) {
                    begL = 0;
                } else {
                    begL = begL - maxCorner;
                }
                uint32_t endL = topLine.getX();
                if (minCorner > endL) {
                    endL = 0;
                } else {
                    endL = endL - minCorner;
                }
                left = v_lines.lower_bound(begL);
                uint32_t leftLim = v_lines.upper_bound(endL)->first;
                
                while (!found && left != v_lines.end() && left->first < leftLim) {
                    
                    Line leftLine = left->second;
                    uint32_t begR = topLine.getX() + topLine.getLength() + minCorner;
                    uint32_t endR = topLine.getX() + topLine.getLength() + maxCorner;
                    right = v_lines.lower_bound(begR);
                    uint32_t rightLim;
                    if (v_lines.upper_bound(endR) == v_lines.end()) {
                        rightLim = v_lines.rbegin()->first;
                    } else {
                        rightLim = v_lines.upper_bound(endR)->first;
                    }
                    while (!found && right != v_lines.end() && right->first < rightLim) {
                        Line rightLine = right->second;
                        if (leftLine.getY() == rightLine.getY() && rightLine.getLength() == leftLine.getLength()) {
                            uint32_t xShift1 = std::abs((int32_t)(leftLine.getX() - topLine.getX()));
                            uint32_t xShift2 = std::abs((int32_t)(rightLine.getX() - (topLine.getX() + topLine.getLength())));
                            uint32_t yShift1 = std::abs((int32_t)(leftLine.getY() - topLine.getY()));
                            uint32_t yShift2 = std::abs((int32_t)((leftLine.getY() + leftLine.getLength()) - bottomLine.getY()));
                            
                            if (xShift1 == xShift2 && yShift1 == yShift2) {
                                found = true;
                            }
                        }
                        if (!found) {
                            ++right;
                        }
                    }
                    if (!found) {
                        ++left;
                    }
                }
                
            }
            if (!found) {
                ++bottom;
            }
        }
        
        if (found) {
            found = false;
            std::pair<uint32_t, uint32_t> tl = top->second.crossing(left->second);
            std::pair<uint32_t, uint32_t> br = bottom->second.crossing(right->second);
            
            res.push_back(bmp.rect(tl.first, tl.second, br.first + 1, br.second + 1));
            
            h_lines.erase(bottom);
            v_lines.erase(left);
            v_lines.erase(right);
        }
        h_lines.erase(top);
        top = h_lines.begin();
        
    }
    
    return res;
}

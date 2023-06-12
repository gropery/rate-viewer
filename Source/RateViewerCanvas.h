/*
------------------------------------------------------------------

This file is part of a plugin for the Open Ephys GUI
Copyright (C) 2022 Open Ephys

------------------------------------------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef RATEVIEWCANVAS_H_INCLUDED
#define RATEVIEWCANVAS_H_INCLUDED

#include <VisualizerWindowHeaders.h>

class RateViewer;

/**
* 
	Draws data in real time

*/
class RateViewerCanvas : public Visualizer
{
public:

	/** Constructor */
	RateViewerCanvas(RateViewer* processor);

	/** Destructor */
	~RateViewerCanvas();

	/** Updates boundaries of sub-components whenever the canvas size changes */
	void resized() override;

	/** Called when the visualizer's tab becomes visible again */
	void refreshState() override;

	/** Updates settings */
	void update() override;

	/** Called instead of "repaint()" to avoid re-painting sub-components*/
	void refresh() override;

	/** Draws the canvas background */
	void paint(Graphics& g) override;

	/** Set the window size for spike rate calculation */
	void setWindowSizeMs(int windowSize_);

	/** Set the bin size for spike rate calculation */
	void setBinSizeMs(int binSize_);

	/** Set the sample rate for the active electrode */
	void setSampleRate(float sampleRate);

	/** Change the plot title*/
	void setPlotTitle(const String& title);

	/** Adds a spike sample number */
	void addSpike(int64 sample_number);

	/** Sets the sample index for the latest buffer*/
	void setMostRecentSample(int64 sampleNum);

private:

	/** Pointer to the processor class */
	RateViewer* processor;

	/** Class for plotting data */
	InteractivePlot plt;

	float sampleRate = 0.0f;

	int windowSize = 1000;
	int binSize = 50;

	Array<int64> incomingSpikeSampleNums;

	int64 mostRecentSample = 0;

	/** Recomputes bin edges */
	void recomputeBinEdges();

	Array<double> binEdges;
	Array<int> spikeCounts;

	/** Recounts spikes/bin; returns true if a new bin is available */
	bool countSpikes();

	int64 sampleOnLastRedraw = 0;
	int maxCount = 1;

	/** Change the XY range of the spike rate plot */
	void updatePlotRange();

	/** Generates an assertion if this class leaks */
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RateViewerCanvas);
};


#endif // SPECTRUMCANVAS_H_INCLUDED
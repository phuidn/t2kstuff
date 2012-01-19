
Everything in the cuts1 folder (this one :D ) was made using these cuts.
		keep = keep? noTPC1(Detectors): 0;
		keep = keep? noP0Dactivity(Detectors): 0;
		keep = keep? posCharge(NTPCs, TPC): 0;
		keep = keep? consecutiveDetectors(Detectors):0;
		keep = keep? muonPull(NTPCs, TPC):0;



Files:
	propull.png:
		Shows the proton pull graph.
		This looks pretty good in comparison to the initial cuts propull graph.
		This is (probably because of the muon cut we made after seeing the muonpull graph from before. - This cut out a lot of muons with very few protons.

		Now we should see how this affects the other variables for each type of reaction.

	propullqes.png
		This was just to show that although we have removed a lot of muons (and hence a lot of NON-QES reactions) that we still have a fairly low amount of NCQES reactions.

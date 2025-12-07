function generateSmoothWaveformSVG(totalBars, svgWidth, svgHeight) {
	const centerX = svgWidth / 2;
	const spacing = 8;
	const half = Math.floor(totalBars / 2);

	// Pre-generate rough heights
	let raw = [];
	for (let i = 0; i < totalBars; i++) {
		raw.push(10 + Math.pow(Math.random(), 3) * 40);
	}

	// Smooth them using weighted interpolation
	let smooth = [];
	for (let i = 0; i < raw.length; i++) {
		const prev = raw[i - 1] ?? raw[i];
		const next = raw[i + 1] ?? raw[i];

		// lighter blend: mostly original value
		smooth.push(prev * 0.2 + raw[i] * 0.8 + next * 0.2);
	}

	let svg = `<svg width="${svgWidth}" height="${svgHeight}" viewBox="0 0 ${svgWidth} ${svgHeight}" xmlns="http://www.w3.org/2000/svg">`;

	for (let i = -half; i <= half; i++) {
		const index = i + half;
		const h = smooth[index];
		const x = centerX + i * spacing;

		const y1 = (svgHeight - h) / 2;
		const y2 = y1 + h;

		svg += `<path d="M${x} ${y1}V${y2}" stroke="black" stroke-width="4" stroke-linecap="round"/>`;
	}

	svg += `</svg>`;
	return svg;
}

for (let i = 0; i < 15; i++) {
	const svg = document.createElement("svg");
	svg.innerHTML = generateSmoothWaveformSVG(31, 300, 150);
	svg.onclick = () => console.log(svg.innerHTML);
	document.body.appendChild(svg);
}

window.addEventListener("keydown", (e) => e.key === "a" && window.location.reload());

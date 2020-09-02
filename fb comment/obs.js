
var path = document.querySelector("#mount_0_0 > div > div:nth-child(1) > div.rq0escxv.l9j0dhe7.du4w35lb > div.rq0escxv.l9j0dhe7.du4w35lb > div > div > div.j83agx80.cbu4d94t.d6urw2fd.dp1hu0rb.l9j0dhe7.du4w35lb > div.rq0escxv.l9j0dhe7.du4w35lb.j83agx80.pfnyh3mw.jifvfom9.gs1a9yip.owycx6da.btwxx1t3.buofh1pr.dp1hu0rb.ka73uehy > div.rq0escxv.l9j0dhe7.tkr6xdv7.j83agx80.cbu4d94t.pfnyh3mw.d2edcug0.hpfvmrgz.dp1hu0rb.rek2kq2y.o36gj0jk > div > div.q5bimw55.rpm2j7zs.k7i0oixp.gvuykj2m.j83agx80.cbu4d94t.ni8dbmo4.eg9m0zos.l9j0dhe7.du4w35lb.ofs802cu.pohlnb88.dkue75c7.mb9wzai9.d8ncny3e.buofh1pr.g5gj957u.tgvbjcpo.l56l04vs.r57mb794.kh7kg01d.c3g1iek1.k4xni2cv > div.j83agx80.cbu4d94t.buofh1pr > div.aov4n071.j83agx80.cbu4d94t.buofh1pr > div > div.buofh1pr.j83agx80.aovydwv3 > div > div > div > div")


var observer = new MutationObserver(callback);
observer.observe(path, { childList: true });

// Hide all elements in this page that is not ours, a script, or a link tag.
for (var i=0; i<document.body.children.length; i++) {
	document.body.children[i].style.display = "none"
}

// Create our very own container
var container = document.createElement("div");
container.id = "obs";
document.body.appendChild(container);

// Put our own stylesheet

var style = document.createElement("style");
style.type = "text/css";

var styleContent = document.createTextNode('html{font-family: "Tahoma"; font-size:64px; font-weight: bold;} body{background:rgba(0,0,0,0) !important;overflow: hidden !important;} #obs{width:100vw;} #obs span{color:#c93c75} #obs p{color: white; text-shadow: -4px -4px 0 #000, 4px -4px 0 #000, -4px  4px 0 #000, 4px  4px 0 #000;}');
style.appendChild(styleContent);
document.head.appendChild(style)

function callback(mutationList, observer) {
	mutationList.forEach( (mutation) => {
	  	switch(mutation.type) {
			case 'childList':

				var result = path.children[path.childElementCount - 1].querySelectorAll('[dir="auto"]');
				var text = ''
				
				if (result.length == 3) {
					text = `<p><span>${result[0].innerHTML}:</span> ${result[2].innerHTML}`
				} else {
					text = `<p><span>${result[1].innerHTML}:</span> ${result[3].innerHTML}`
				}

				container.insertAdjacentHTML("beforeend", text);
				
				// Scroll to the last comment
				container.scrollTop = container.scrollHeight

				break;
	  	}
	});
}
  
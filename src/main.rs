/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

mod utils;

use color_eyre::Result;

use crate::utils::logger;

fn main() -> Result<()> {
    color_eyre::install()?;
    logger::init(3)?;

    log::info!("Hello, world!");

    Ok(())
}
